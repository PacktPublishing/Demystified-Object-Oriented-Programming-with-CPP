// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To understand the copy constructor.

#include <iostream>  
#include <cstring>     // though we'll prefer std::string, we will need to illustrate one dynamically allocated
                       // data member to show several important concepts in this chapter (so we'll use a single char *)

using std::cout;       // preferred to: using namespace std;
using std::endl;
using std::string;

class Student
{
private: 
    // data members
    string firstName;
    string lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;    // though we'll prefer std::string, this data member will help us illustrate a few important ideas
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, float, const char *); 
    Student(const Student &);  // copy constructor prototype
    void CleanUp();
    void Print();
    void SetFirstName(const string &);
};

// default constructor
Student::Student()
{
    // Remember, firstName and lastName are member objects of type string; they are default constructed and hence
    // 'empty' by default. They HAVE been initialized. 
    middleInitial = '\0';
    gpa = 0.0;
    currentCourse = nullptr;
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, float avg, const char *course)
{
    firstName = fn; 
    lastName = ln; 
    middleInitial = mi;
    gpa = avg;
    currentCourse = new char [strlen(course) + 1];  // // remember to dynamically allocate the memory for data members that are pointers
    strcpy(currentCourse, course);
}

// Copy constructor definition - implements a deep copy
Student::Student(const Student &s)
{
    firstName = s.firstName;   // string will do a deep assignment for us
    lastName = s.lastName;
    middleInitial = s.middleInitial;
    gpa = s.gpa;
    // for ptr data member -- allocate necessary memory for destination string
    currentCourse = new char [strlen(s.currentCourse) + 1];
    // then copy source to destination string
    strcpy(currentCourse, s.currentCourse);
}

// Member function definition
void Student::CleanUp()
{
    delete currentCourse;   // deallocate the memory for data members that are pointers
}
   
// Member function definition
void Student::Print()
{
    cout << firstName << " " << middleInitial << ". ";
    cout << lastName << " has a gpa of: " << gpa;
    cout << " and is enrolled in: " << currentCourse << endl;
}

void Student::SetFirstName(const string &fn)
{
    firstName = fn;
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
    s2.CleanUp();  // lets call CleanUp() to delete() them
    s3.CleanUp();
    s4.CleanUp();

    return 0;
}
