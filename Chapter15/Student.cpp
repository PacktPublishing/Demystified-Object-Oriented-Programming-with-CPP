// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate Student.cpp Source code

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Student.h"

using std::cout;      // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::move;

Student::Student() : gpa(0.0), currentCourse(""), studentId (0)
{
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const char *t, float avg, const string &course, const char *id) :
                 Person(fn, ln, mi, t), gpa(avg), currentCourse(course)
{
    char *temp = new char [strlen(id) + 1];
    strcpy (temp, id);
    studentId = temp;
}

// Copy constructor definition
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse)
{
    cout << "Student copy constructor" << endl;
    // deep copy of pointer data member (use a temp since data is const and can't be directly copied into)
    char *temp = new char [strlen(s.studentId) + 1];
    strcpy (temp, s.studentId);
    studentId = temp;
}

// move copy constructor
// left hand object overtakes the dynamically allocated data memberse of right hand object
// Then null out right hand objects pointer members (we've relinquished those members). Non-pointer data is just copied.
Student::Student(Student &&s) : Person(move(s))   // make sure we call base class Move copy constructor
{
    cout << "Student move copy constructor" << endl;
    gpa = s.gpa;   // copy then
    s.gpa = 0.0;   // zero out source object member
    currentCourse = s.currentCourse;
    s.currentCourse = "";
    // for ptr data member, destination data member takes over source data member's memory
    studentId = s.studentId;  // data is constant, pointer is not so assignment is ok
    s.studentId = nullptr;    // then null out source pointer data member
}

// destructor definition
Student::~Student()
{
    cout << "Student destructor" << endl;
    delete (char *) studentId;    // fix cast
}

void Student::EarnPhD()
{
    ModifyTitle("Dr.");
}

void Student::Print() const
{   // need to use access functions as these data members are
    // defined in Person as private
    if (GetTitle())
        cout << GetTitle() << " ";
    if (!GetFirstName().empty())
        cout << GetFirstName() << " ";
    else
        cout << "No first name" << " ";
    if (GetMiddleInitial() != '\0')
        cout << GetMiddleInitial() << ". ";
    if (!GetLastName().empty())
        cout << GetLastName();
    if (studentId)
        cout << " with id: " << studentId;
    if (gpa != 0.0)
        cout << " GPA: " << setprecision(3) <<  " " << gpa;
    if (!currentCourse.empty())
        cout << " Course: " << currentCourse << endl;
    else
        cout << " No current course" << endl;
}

void Student::IsA() const
{
    cout << "Student" << endl;
}

// overloaded assignment operator
Student &Student::operator=(const Student &s)
{
   cout << "Student assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &s)
   {
      Person::operator=(s);  // call base class operator= for help

      // delete memory for existing destination data members that are pointers
      delete studentId;

      // for ptr data members, make a deep assignment -- reallocate memory then copy.
      // for non-ptr data members, an assignment is just fine
      gpa = s.gpa;
      currentCourse = s.currentCourse;
      // deep copy of pointer data member (use a temp since data is const and can't be directly copied into)
      char *temp = new char [strlen(s.studentId) + 1];
      strcpy (temp, s.studentId);
      studentId = temp;
   }
   return *this;  // allow for cascaded assignments
}

// overloaded move assignment operator
Student &Student::operator=(Student &&s)
{
   cout << "Student Move assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &s)
   {
      Person::operator=(move(s));  // call base class operator= for help

      // delete lhs original data members that are pointers
      delete studentId;

      // Take over rhs object's data members (at least those which are pointers)
      // Once data members are taken over by lhs, null out the rhs object's pointer to them
      // for non-pointer members, an assignment is fine
      gpa = s.gpa;
      s.gpa = 0.0;  // zero out source objects data member value
      currentCourse = s.currentCourse;  // take over memory from pointer data members
      s.currentCourse = "";
      // for ptr data members, destination data member will take over source data member's memory
      studentId = s.studentId;  // this is a pointer assignment
      s.studentId = nullptr;      // null out source object's data member (so they won't share the memory)
   }
   return *this;  // allow for cascaded assignments
}

