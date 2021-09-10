// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate Student.h header file 

#ifndef _STUDENT_H
#define _STUDENT_H

#include "Person.h"

class Student : public Person
{
private:
    // data members
    float gpa = 0.0;     // in-class initialization
    string currentCourse;
    const char *studentId;     // Again, we have one pointer data member to demonstrate deep copy / assignment
    static int numStudents;
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const char *,
            float, const string &, const char *);
    Student(const Student &);  // copy constructor
    Student(Student &&); // move copy constructor
    ~Student() override;  // virtual destructor
    void EarnPhD();
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const char *GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only

    // In the derived class, the keyword virtual is optional for overridden (polymorphic) methods, as is the keyword "override"
    // Currently, "override" is recommended for internal documentation, however "virtual" is not recommended
    void Print() const override;
    void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const Student &) const
    Student &operator=(const Student &);  // overloaded assignment operator prototype
    Student &operator=(Student &&);  // overloaded move assignment operator prototype

    static int GetNumberStudents();  
};

inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
}

#endif
