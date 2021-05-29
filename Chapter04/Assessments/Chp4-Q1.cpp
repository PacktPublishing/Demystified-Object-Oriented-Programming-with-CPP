// (c) Dorothy R. Kirk. All Rights Reserved.
// Chapter 4, Question 1, a - c, Sample Solution

// Modify and augment your C++ program from Chapter 3, Indirect Addressing – Pointers, Exercise 1 as follows:
// a. Overload your ReadData() function, with a version that accepts a Student & parameter to allow firstName, 
// lastName, currentCourseEnrolled, and gpa to be entered from the keyboard within the function.
// b. Replace the Print() function which takes a Student from your previous solution to instead take a const 
// Student & as a parameter for Print().
// c. Create variables of type Student and of type Student * in main(). Now, call the various versions of 
// ReadData(), and Print(). 

#include <iomanip>
#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::string;

const int MAX = 5;

class Student
{
public:
    string firstName;
    string lastName;
    float gpa;
    string course;
};

// function prototypes 
void Print(const Student *);
void Print(const Student &);    // note: this version is instead of void Print(Student); Having both creates ambiguity
void ReadData(Student *);
void ReadData(Student &);

int main()
{
    Student s1, s2;
    Student *s3 = new Student;
    Student *s4 = new Student;
    ReadData(s1);   // reference version
    ReadData(&s2);  // pointer version 
    ReadData(s3);   // pointer version
    ReadData(*s4);  // reference version 

    Print(s1);      // ref version
    Print(&s2);     // pointer version
    Print(s3);      // pointer version
    Print(*s4);     // reference version

    return 0;
}

void Print(const Student *s)
{
    cout << "void Print(const Student *)" << endl;
    cout << s->firstName << " " << s->lastName << " is taking " << s->course;
    cout << " and has a gpa of " << std::setprecision(3) << s->gpa << endl;
}

void Print(const Student &s)
{
    cout << "void Print(const Student &)" << endl;
    cout << s.firstName << " " << s.lastName << " is taking " << s.course;
    cout << " and has a gpa of " << std::setprecision(3) << s.gpa << endl;
}

void ReadData(Student *s)
{
    cout << "void ReadData(Student *)" << endl;
    cout << "Please enter <firstname> <lastname>: ";
    cin >> s->firstName >> s->lastName;
    cout << "Please enter " << s->firstName << " " << s->lastName;
    cout << "'s <gpa> and <course>: ";
    cin >> s->gpa >> s->course;
}

void ReadData(Student &s)
{
    cout << "void ReadData(Student &)" << endl;
    cout << "Please enter <firstname> <lastname>: ";
    cin >> s.firstName >> s.lastName;
    cout << "Please enter " << s.firstName << " " << s.lastName;
    cout << "'s <gpa> and <course>: ";
    cin >> s.gpa >> s.course;
}

