// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate pImpl pattern, version using native (raw) pointers 

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Person.h"

using namespace std;

// Nested class definition supports implementation
class Person::PersonImpl
{
private: 
    char *firstName;
    char *lastName;
    char middleInitial;
    char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
public:
    PersonImpl();   
    PersonImpl(const char *, const char *, char, const char *);  
    PersonImpl(const PersonImpl &);  // copy constructor
    virtual ~PersonImpl();  
    const char *GetFirstName() const { return firstName; }  
    const char *GetLastName() const { return lastName; }    
    const char *GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }
    void ModifyTitle(const char *); 
    virtual void Print() const;
    virtual void IsA() { cout << "Person" << endl; }
    virtual void Greeting(const char *msg) { cout << msg << endl; }
    PersonImpl &operator=(const PersonImpl &);  // overloaded assignment operator prototype
};


// Nested class member functions

Person::PersonImpl::PersonImpl()
{
    firstName = lastName = 0;  // NULL pointer
    middleInitial = '\0';
    title = 0;
}

Person::PersonImpl::PersonImpl(const char *fn, const char *ln, char mi, const char *t)
{
    firstName = new char [strlen(fn) + 1];
    strcpy(firstName, fn);
    lastName = new char [strlen(ln) + 1];
    strcpy(lastName, ln);
    middleInitial = mi;
    title = new char [strlen(t) + 1];
    strcpy(title, t);
}

Person::PersonImpl::PersonImpl(const Person::PersonImpl &pers) 
{
    firstName = new char [strlen(pers.firstName) + 1];
    strcpy(firstName, pers.firstName);
    lastName = new char [strlen(pers.lastName) + 1];
    strcpy(lastName, pers.lastName);
    middleInitial = pers.middleInitial;
    title = new char [strlen(pers.title) + 1];
    strcpy(title, pers.title);
}

Person::PersonImpl::~PersonImpl()
{
    delete firstName;
    delete lastName;
    delete title;
}

void Person::PersonImpl::ModifyTitle(const char *newTitle)
{
    delete title;  // delete old title
    title = new char [strlen(newTitle) + 1];
    strcpy(title, newTitle);
}

void Person::PersonImpl::Print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". ";
    cout << lastName << endl;
}

Person::PersonImpl &Person::PersonImpl::operator=(const PersonImpl &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      delete firstName;  // or call ~Person();
      delete lastName;
      delete title;

      firstName = new char [strlen(p.firstName) + 1];
      strcpy(firstName, p.firstName);
      lastName = new char [strlen(p.lastName) + 1];
      strcpy(lastName, p.lastName);
      middleInitial = p.middleInitial;
      title = new char [strlen(p.title) + 1];
      strcpy(title, p.title);
   }
   return *this;  // allow for cascaded assignments
}


// Person member functions

Person::Person() : pImpl(new PersonImpl())
{
}

Person::Person(const char *fn, const char *ln, char mi, 
               const char *t) : pImpl(new PersonImpl(fn, ln, mi, t))
{
}

// copy constructor -- in member init list, call PersonImpl copy constructor with new nested object creation
Person::Person(const Person &pers): pImpl(new PersonImpl(*(pers.pImpl))) 
{
    // No Person data members to copy from pers except deep copy in *(pers.pImpl)
    // Note: line below is an alternative to initialization in member initialization list
    // pImpl = new PersonImpl(*(pers.pImpl));  // call PersonImpl copy constructor with new nested object creation
}

Person::~Person()
{
    delete pImpl;   // delete associated implementation
}

// Notice that simple access functions are no longer inline

const char *Person::GetFirstName() const
{
    return pImpl->GetFirstName();
}

const char *Person::GetLastName() const
{
    return pImpl->GetLastName();
}

const char *Person::GetTitle() const
{
    return pImpl->GetTitle();
}

char Person::GetMiddleInitial() const
{
    return pImpl->GetMiddleInitial();
}

void Person::ModifyTitle(const char *newTitle)
{
    pImpl->ModifyTitle(newTitle);  // delegate to implementation
}

void Person::Print() const
{
    pImpl->Print();   // delegate to implementation
}

void Person::IsA()
{
    pImpl->IsA();   // delegate to implementation
}

void Person::Greeting(const char *msg)
{
    pImpl->Greeting(msg);    // delegate to implementation
}

Person &Person::operator=(const Person &p)
{
   // no data members, other than pImpl, in Person to do a deep assignment
   // Note: p.pImpl is a pointer; must dereference with * to get a referencable object
   pImpl->operator=(*(p.pImpl));   // call op= on impl piece
   return *this;  // allow for cascaded assignments
}
