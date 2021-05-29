// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate inline functions.

#include <iostream>  
#include <cstring> 
using namespace std;

class Student
{
private: 
    // data members
    char *firstName;
    char *lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;
public:
    // member function prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, float, const char *); 
    Student(const Student &);  // copy constructor
    ~Student();  // destructor
    void Print();

    // inline function definitions
    // firstName is returned as a const string
    const char *GetFirstName() { return firstName; }  
    const char *GetLastName() { return lastName; }    
    char GetMiddleInitial() { return middleInitial; }
    float GetGpa() { return gpa; }
    const char *GetCurrentCourse() { return currentCourse; }

    // prototype only, see inline function definiton below
    void SetCurrentCourse(const char *);
};

inline void Student::SetCurrentCourse(const char *c)
{
    delete currentCourse;  
    currentCourse = new char [strlen(c) + 1];
    strcpy(currentCourse, c); 
}
// Definitions for default, alternate, copy constructor,
// the destructor, and Print() have been omitted for space,
// but are same as last example for class Student

// default constructor
Student::Student()
{
    firstName = lastName = 0;  // NULL pointer
    middleInitial = '\0';
    gpa = 0.0;
    currentCourse = 0;
}

// Alternate constructor member function definition
Student::Student(const char *fn, const char *ln, char mi, 
                 float avg, const char *course)
{
    firstName = new char [strlen(fn) + 1];
    strcpy(firstName, fn);
    lastName = new char [strlen(ln) + 1];
    strcpy(lastName, ln);
    middleInitial = mi;
    gpa = avg;
    currentCourse = new char [strlen(course) + 1];
    strcpy(currentCourse, course);
}

// Copy constructor definition  implement a deep copy
Student::Student(const Student &s)
{
    // allocate necessary memory for destination string
    firstName = new char [strlen(s.firstName) + 1];
    // then copy source to destination string
    strcpy(firstName, s.firstName);
    lastName = new char [strlen(s.lastName) + 1];
    // data members which are not pointers do not need their
    // space allocated for deep copy, such as is done above
    strcpy(lastName, s.lastName);
    middleInitial = s.middleInitial;
    gpa = s.gpa;
    // allocate destination string space, then copy contents
    currentCourse = new char [strlen(s.currentCourse) + 1];
    strcpy(currentCourse, s.currentCourse);
}

// Member function definition
Student::~Student()
{
    delete firstName;
    delete lastName;
    delete currentCourse;
}
   
// Member function definition
void Student::Print()
{
    cout << firstName << " " << middleInitial << ". ";
    cout << lastName << " has a gpa of: " << gpa;
    cout << " and is enrolled in: " << currentCourse << endl;
}


int main()
{
    Student s1("Jo", "Muritz", 'Z', 4.0, "C++"); 

    cout << s1.GetFirstName() << " " << s1.GetLastName();
    cout << " Enrolled in: " << s1.GetCurrentCourse() << endl;

    s1.SetCurrentCourse("Advanced C++ Programming");
   
    cout << s1.GetFirstName() << " " << s1.GetLastName();
    cout << " New course: " << s1.GetCurrentCourse() << endl;

    return 0;
}

