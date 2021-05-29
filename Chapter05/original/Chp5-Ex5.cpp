// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To understand the copy constructor.

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
    Student(const Student &);  // copy constructor prototype
    void CleanUp();
    void Print();
    void SetFirstName(const char *);
};

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

// Copy constructor definition - implements a deep copy
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
void Student::CleanUp()
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

void Student::SetFirstName(const char *n)
{
    delete firstName; // delete existing name
    firstName = new char [strlen(n) + 1];
    strcpy(firstName, n);
}

int main()
{ 
    // instantiate two Students
    Student s1("Zachary", "Moon", 'R', 3.7, "C++");
    Student s2("Gabrielle", "Doone", 'A', 3.7, "C++");

    // These initializations implicitly invoke copy constructor
    Student s3(s1);  
    Student s4 = s2;
    s3.SetFirstName("Zack");  // alter each object slightly
    s4.SetFirstName("Gabby");

    // This sequence does not invoke copy constructor 
    // This is instead an assignment.
    // Student s5("Giselle", "LeBrun", 'A', 3.1, "C++);
    // Student s6;
    // s6 = s5;  // this is an assignment, not initialization

    s1.Print();   // print each instance
    s3.Print();
    s2.Print();
    s4.Print();

    s1.CleanUp();  // Since some data members are pointers,
    s2.CleanUp(); // lets call a function to delete() them
    s3.CleanUp();
    s4.CleanUp();

    return 0;
}
