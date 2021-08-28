// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate pImpl pattern, this version uses a unique pointer as association from Person to PersonImpl 
// Note: destructor in Person no longer has to delete the associated implementation (managed by unique pointer)

#include <iostream>
#include <iomanip>
#include "Person.h"

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;
// using std::unique_ptr;

// Nested class definition supports implementation
class Person::PersonImpl
{
private: 
    string firstName;
    string lastName;
    char middleInitial;
    string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
public:
    PersonImpl();   // default constructor
    PersonImpl(const string &, const string &, char, const string &);  
    PersonImpl(const PersonImpl &);  // copy constructor
    virtual ~PersonImpl();  // virtual destructor

    const string &GetFirstName() const { return firstName; }  
    const string &GetLastName() const { return lastName; }    
    const string &GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }
    void ModifyTitle(const string &); 

    virtual void Print() const;
    virtual void IsA() const;  
    virtual void Greeting(const string &);

    PersonImpl &operator=(const PersonImpl &);  // overloaded assignment operator prototype
};

// Nested class member functions

Person::PersonImpl::PersonImpl() : firstName(""), lastName(""), middleInitial('\0'), title("")
{
}

Person::PersonImpl::PersonImpl(const string &fn, const string &ln, char mi, const string &t) :
                               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person::PersonImpl::PersonImpl(const Person::PersonImpl &p) : firstName(p.firstName), lastName(p.lastName),
                                                              middleInitial(p.middleInitial), title(p.title)
{
}

Person::PersonImpl::~PersonImpl()
{
}

void Person::PersonImpl::ModifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::PersonImpl::Print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". ";
    cout << lastName << endl;
}

void Person::PersonImpl::IsA() const
{
    cout << "Person" << endl;
}

void Person::PersonImpl::Greeting(const string &msg)
{
    cout << msg << endl;
}

Person::PersonImpl &Person::PersonImpl::operator=(const PersonImpl &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = p.title;
   }
   return *this;  // allow for cascaded assignments
}


// Person member functions

Person::Person() : pImpl(new PersonImpl())
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : pImpl(new PersonImpl(fn, ln, mi, t))
{
}

// copy constructor -- in member init list, call PersonImpl copy constructor with new nested object creation
Person::Person(const Person &p): pImpl(new PersonImpl(*(p.pImpl)))
{
    // No Person data members to copy from pers except deep copy in *(p.pImpl)
    // line below is an alternative to initialization in member initialization list
    // pImpl = new PersonImpl(*(p.pImpl));  // call PersonImpl copy constructor with new nested object creation
}

Person::~Person()
{
    // delete on pImpl no longer required
}

const string &Person::GetFirstName() const
{
    return pImpl->GetFirstName();
}

const string &Person::GetLastName() const
{
    return pImpl->GetLastName();
}

const string &Person::GetTitle() const
{
    return pImpl->GetTitle();
}

char Person::GetMiddleInitial() const
{
    return pImpl->GetMiddleInitial();
}

void Person::ModifyTitle(const string &newTitle)
{
    pImpl->ModifyTitle(newTitle);  // delegate to implementation
}

void Person::Print() const
{
    pImpl->Print();   // delegate to implementation
}

void Person::IsA() const
{
    pImpl->IsA();   // delegate to implementation
}

void Person::Greeting(const string &msg) const
{
    pImpl->Greeting(msg);    // delegate to implementation
}

Person &Person::operator=(const Person &p)
{
   // no data members, other than pImpl, in Person to do a deep assignment
   // note: p.pImpl is a pointer; must dereference with * to get a referencable object
   pImpl->operator=(*(p.pImpl));   // call op= on impl piece
   return *this;  // allow for cascaded assignments
}


