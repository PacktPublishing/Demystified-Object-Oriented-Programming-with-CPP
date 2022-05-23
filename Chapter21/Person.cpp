// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Basic implementation of Person class 

#include <iostream>
#include <iomanip>
#include "Person.h"

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::string;


// Remember, we're using system provided default constructor (and in-class initialization)

// Alternate constructor
Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t), greeting("Hello")

{
}

// We're using default copy constructor, but if we wrote it, it would look like:
/*
Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
                                  middleInitial(p.middleInitial), title(p.title), greeting(p.greeting)
{
}
*/

// Demonstrating simple overloaded operator= implementation
Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      // Note: there's no dynamically allocated data members, so implementing = is straightforward
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = p.title;
      greeting = p.greeting;
   }
   return *this;  // allow for cascaded assignments
}

Person::~Person()
{
   cout << "Person destructor" << endl;
}

void Person::ModifyTitle(const string &newTitle)
{
   title = newTitle;
}

void Person::SetGreeting(const string &newGreeting)
{
   greeting = newGreeting;
}


void Person::Print() const
{
   cout << title << " " << firstName << " " << lastName << endl;
}
