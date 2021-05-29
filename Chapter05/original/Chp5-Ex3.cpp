// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To examine access regions.

#include <iostream>
#include <cstring>
using namespace std;

class Student
{
// private members are accessible only within the scope of
// the class (e.g. within member functions or friends) 
private: 
    char *firstName;   // data members
    char *lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;
    char *studentId;  
// public members are accessible from any scope
public:
    // member function prototypes
    void Initialize();  
    void Initialize(const char *, const char *, char, float, 
                    const char *, const char *);
    void CleanUp();
    void Print();
};

void Student::Initialize()
{
    firstName = lastName = 0;  // NULL pointer
    middleInitial = '\0';      // null character
    gpa = 0.0;
    currentCourse = studentId = 0;
}

// Overloaded member function definition
void Student::Initialize(const char *fn, const char *ln, char mi, 
       float avg, const char *course, const char *id) 
{
    firstName = new char [strlen(fn) + 1];
    strcpy(firstName, fn);
    lastName = new char [strlen(ln) + 1];
    strcpy(lastName, ln);
    middleInitial = mi; 
    gpa = avg;   
    currentCourse = new char [strlen(course) + 1];
    strcpy(currentCourse, course);
    studentId = new char [strlen(id) + 1];
    strcpy (studentId, id); 
}

// Member function definition
void Student::CleanUp()
{
    delete firstName;
    delete lastName;
    delete currentCourse;
    delete studentId;
}

// Member function definition
void Student::Print()
{
    cout << firstName << " " << middleInitial << ". ";
    cout << lastName << " with id: " << studentId;
    cout << " has gpa: " << gpa << " and enrolled in: ";
    cout << currentCourse << endl;
}

int main()
{
    Student s1;

    // Initialize() is public; accessible from any scope
    s1.Initialize("Ming", "Li", 'I', 3.9, "C++", "178GW"); 

    s1.Print();  // Print() is public, accessible from main() 

    // Error! firstName is private; not accessible in main()
    // cout << s1.firstName << endl;  

    // CleanUp() is public, accessible from any scope
    s1.CleanUp(); 

    return 0;
}

