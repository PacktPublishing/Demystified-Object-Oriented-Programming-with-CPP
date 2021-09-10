// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate Person.cpp source code 
// Note: one pointer data member is present to demonstrate deep copy / deep assignment thoroughly

#include <iostream>
#include <iomanip>
#include <cstring>   // we'll generally prefer string, but one char * is used to demonstrate deep copy / deep assignment
#include "Person.h"

using std::cout;     // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::move;

// Remember, we're using system supplied default constructor. Data members middleInitial and title will be set using in-class initialization.

Person::Person(const string &fn, const string &ln, char mi, const char *t) : firstName(fn), lastName(ln), middleInitial(mi)
{
    // allocate memory for ptr data member, then fill with appropriate value
    title = new char [strlen(t) + 1];
    strcpy(title, t);
}

// copy constructor
Person::Person(const Person &p): firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial)
{
    cout << "Person copy constructor" << endl;
    // be sure to do a deep copy for the pointer data member -- allocate memory, then copy contents
    title = new char [strlen(p.title) + 1];
    strcpy(title, p.title);
}

// move copy constructor
// left hand object overtakes the dynamically allocated data members of right hand object
// Then null out right hand objects pointers (we've relinquished those members). Non-pointer data is just copied.
// Non-pointer data members (such as string or single char) are simply copied (string ensures a deep copy with =)
Person::Person(Person &&p)
{
    cout << "Person Move copy constructor" << endl;
    firstName = p.firstName;    
    p.firstName.clear();     // set source object member to empty string
    lastName = p.lastName;
    p.lastName.clear(); 
    middleInitial = p.middleInitial;
    p.middleInitial = '\0';   // set source object member to null character
    title = p.title;     // here, destinatation pointer takes over source pointer's memory
    p.title = nullptr;         // null out source pointer since memory should not be shared (it now belong to destination object)
}

Person::~Person()
{
    cout << "Person destructor" << endl;
    delete title;
}

void Person::ModifyTitle(const string &newTitle)
{
    delete title;  // delete old title
    title = new char[strlen(newTitle.c_str()) + 1];   // get the c string equivalent from the string
    strcpy(title, newTitle.c_str());

}

const string &Person::SetLastName(const string &ln)
{ 
    lastName = ln; 
    return lastName;
}

void Person::Print() const
{
    if (title)
       cout << title << " ";
    if (!firstName.empty())
       cout << firstName << " ";
    else
       cout << "No first name ";
    if (middleInitial != '\0')
       cout << middleInitial << ". ";
    if (!lastName.empty())
       cout << lastName << endl;
    else
       cout << "No last name" << endl;
}

void Person::IsA() const
{
    cout << "Person" << endl;
}

void Person::Greeting(const string &msg) const
{
    cout << msg << endl;
}

// overloaded assignment operator
Person &Person::operator=(const Person &p)
{
   cout << "Person assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      // delete memory for dynamically allocated data members
      delete title;   // or call ~Person(); -- unusual

      // re-allocate memory for pointer data members
      // copy each data member from source to destination object
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = new char [strlen(p.title) + 1];   // mem allocation for ptr member
      strcpy(title, p.title);

   }
   return *this;  // allow for cascaded assignments
}

// overloaded move assignment operator
Person &Person::operator=(Person &&p)
{
   cout << "Person move assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      // delete lhs original memory for pointer data members 
      delete title;    // or call ~Person() - unusual

      // Take over rhs object's data members (at least those which are pointers)
      // Once pointer data members are taken over by lhs, null out the rhs object's pointer to them
      // Non-pointer data members can be copied easily via assignment and then set to a zeroed or empty type value
      firstName = p.firstName;  // assignment between strings will be deep assignment
      p.firstName.clear();         // set source data member to empty string to indicate non-use/existence
      lastName = p.lastName; 
      p.lastName.clear();
      middleInitial = p.middleInitial;
      p.middleInitial = '\0';
      title = p.title;    // with ptr data member, this is a pointer assignemt - destination takes over source object's memory
      p.title = nullptr;
   }
   return *this;  // allow for cascaded assignments
}


