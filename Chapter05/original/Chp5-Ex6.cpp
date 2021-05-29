// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To demonstrate a converstion constructor.

#include <iostream>   
#include <cstring>   
using namespace std;

class Student;  // forward declaration of Student class

class Employee
{
private:
    char firstName[20];
    char lastName[20];
    float salary;
public:
    Employee();
    Employee(const char *, const char *, float);
    Employee(Student &);  // conversion constructor
    void Print();
};

class Student
{
private: // data members
    char *firstName;
    char *lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;
public:
    // constructor prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, float, 
            const char *);
    Student(const Student &);  // copy constructor
    void Print();
    void CleanUp();
    float GetGpa(); // access function for private data member
    const char *GetFirstName();
    const char *GetLastName();
};

Employee::Employee()  // default constructor
{
    firstName[0] = lastName[0] = '\0';  // null character
    salary = 0.0;
}

// alternate constructor
Employee::Employee(const char *fn, const char *ln, 
                   float money)
{
    strcpy(firstName, fn);
    strcpy(lastName, ln);
    salary = money;
}

// conversion constructor -argument is a Student not Employee
// provide a meaningful transformation from a Student to an Employee
Employee::Employee(Student &s)
{
    strcpy(firstName, s.GetFirstName());
    strcpy(lastName, s.GetLastName());
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

float Student::GetGpa()
{
    return gpa;
}

const char *Student::GetFirstName()
{
    return firstName;
}

const char *Student::GetLastName()
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

