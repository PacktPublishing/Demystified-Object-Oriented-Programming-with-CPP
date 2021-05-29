// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To examine access regions.

#include <iostream>
#include <cstring>     // though we'll prefer std::string, we will need to illustrate one dynamically allocated
                       // data member to show several important concepts in this chapter (so we'll use a single char *)

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Student
{
// private members are accessible only within the scope of
// the class (e.g. within member functions or friends) 
private: 
    string firstName;   // data members
    string lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;    // though we'll prefer std::string, this data member will help us illustrate a few important ideas
// public members are accessible from any scope
public:
    // member function prototypes
    void Initialize();  
    void Initialize(string, string, char, float, const char *);
    void CleanUp();
    void Print();
};

void Student::Initialize()
{
    // even though string data members, firstName and lastName, are initialized with empty strings (string is a class and does so for us),
    // it is considered better practice to ensure that all data members are set ourselves 
    firstName = "";
    lastName = "";
    middleInitial = '\0';      // null character
    gpa = 0.0;
    currentCourse = nullptr;
}

// Overloaded member function definition
void Student::Initialize(string fn, string ln, char mi, float avg, const char *course) 
{
    firstName = fn; 
    lastName = ln; 
    middleInitial = mi; 
    gpa = avg;   
    currentCourse = new char [strlen(course) + 1];   // remember to dynamically allocate the memory for data members that are pointers
    strcpy(currentCourse, course);
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
    cout << lastName << " has gpa: " << gpa;
    cout << " and enrolled in: " << currentCourse << endl;
}

int main()
{
    Student s1;

    // Initialize() is public; accessible from any scope
    s1.Initialize("Ming", "Li", 'I', 3.9, "C++"); 

    s1.Print();  // Print() is public, accessible from main() 

    // Error! firstName is private; not accessible in main()
    // cout << s1.firstName << endl;  

    // CleanUp() is public, accessible from any scope
    s1.CleanUp(); 

    return 0;
}

