// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To demonstrate a converstion constructor.

#include <iostream>   
#include <cstring>      // though we'll prefer std::string, we will need to illustrate one dynamically allocated
                        // data member to show several important concepts in this chapter (so we'll use a single char *)

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Student;  // forward declaration of Student class

class Employee
{
private:
    string firstName;
    string lastName;
    float salary;
public:
    Employee();
    Employee(const string &, const string &, float);
    Employee(Student &);  // conversion constructor
    void Print();
};

class Student
{
private: // data members
    string firstName;
    string lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;   // though we'll prefer std::string, this data member will help us illustrate a few important ideas
public:
    // constructor prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, float, const char *);
    Student(const Student &);  // copy constructor
    void Print();
    void CleanUp();
    float GetGpa(); // access function for private data member
    const string &GetFirstName();
    const string &GetLastName();
};

Employee::Employee()  // default constructor
{
    // Remember, firstName and lastName are member objects of type string; they are default constructed and hence
    // 'empty' by default. They HAVE been initialized. 
    salary = 0.0;
}

// alternate constructor
Employee::Employee(const string &fn, const string &ln, float money)
{
    firstName = fn;
    lastName = ln;
    salary = money;
}

// conversion constructor - argument is a Student not Employee
// Purpose: to provide a meaningful transformation from a Student to an Employee
// Eventually, we can properly const qualify parameter, but
// we’ll need to learn about const member functions first… 
Employee::Employee(Student &s)
{
    firstName = s.GetFirstName();
    lastName = s.GetLastName();
    if (s.GetGpa() >= 4.0)
        salary = 75000;
    else if (s.GetGpa() >= 3.0)
        salary = 60000;
    else
        salary = 50000; 
}

void Employee::Print()
{
    cout << firstName << " " << lastName << " " << salary;
    cout << endl;
}

// default constructor
Student::Student()
{
    // even though string data members, firstName and lastName, are initialized with empty strings (string is a class and does so for us),
    // it is considered better practice to ensure that we initialize all data members within our constructor
    firstName = "";
    lastName = "";
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
    currentCourse = new char [strlen(course) + 1];  // remember to dynamically allocate the memory for data members that are pointers
    strcpy(currentCourse, course);
}

// Copy constructor definition  implement a deep copy
Student::Student(const Student &s)
{
    firstName = s.firstName;
    lastName = s.lastName;
    middleInitial = s.middleInitial;
    gpa = s.gpa;
    // for ptr data members -- allocate necessary memory for destination string
    currentCourse = new char [strlen(s.currentCourse) + 1];
    // then copy source to destination string
    strcpy(currentCourse, s.currentCourse);
}

// Member function definition
void Student::CleanUp()
{
    delete currentCourse;    // deallocate the memory for data members that are pointers
}
   
// Member function definition
void Student::Print()
{
    cout << firstName << " " << middleInitial << ". ";
    cout << lastName << " has a gpa of: " << gpa;
    cout << " and is enrolled in: " << currentCourse << endl;
}

float Student::GetGpa()
{
    return gpa;
}

const string &Student::GetFirstName()
{
    return firstName;
}

const string &Student::GetLastName()
{
    return lastName;
}

int main()
{
    Student s1("Giselle", "LeBrun", 'A', 3.5, "C++");
    Employee e1(s1);  // conversion constructor
    e1.Print();
    s1.CleanUp();  // CleanUp() will delete() s1's dynamically
                   // allocated data members
    return 0;     
}

