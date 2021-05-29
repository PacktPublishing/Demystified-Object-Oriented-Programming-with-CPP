// (c) Dorothy R. Kirk. All Rights Reserved
// Chapter 3, Question 1, a - f. Sample Solution

// Modify and augment your C++ program from Chapter 2, Adding Language Necessities, Exercise 2 as follows:
// a. Create a function, ReadData(), which accepts a pointer to a Student as an argument to allow for 
// firstName, lastName, gpa, and the currentCourseEnrolled to be entered from the keyboard within the 
// function and stored as the input parameter’s data.
// b. Modify firstName, lastName, and currentCourseEnrolled to be modelled as char * (or string) in your 
// Student class instead of using fixed sized arrays (as they may have been modelled in Chapter 2, Adding 
// Language Necessities). If using char *, you may utilize a temp variable which is a fixed size to initially 
// capture user input for these values, and then allocate the proper, respective sizes for each of these data members. 
// Note that using a string will be the simplest and safest approach. 
// c. Rewrite, if necessary, the Print() function from your solution in Chapter 2, Adding Language Necessities  
// to take a Student as a parameter for Print().
// d. Overload the Print() function with one which takes a const Student * as a parameter. Which one is 
// more efficient? Why?
// e. In main(), create an array of pointers to Student to accommodate 5 students. Allocate each Student, 
// call ReadData() for each Student and then Print() each Student using a selection from your above functions. 
// When done, remember to delete() the memory for each student allocated.
// f. Also in main(), create an array of void pointers which is the same size as the array of pointers to Student. 
// Set each element in the array of void pointers to point to a corresponding Student from the array of 
// Student pointers. Call the version of Print() which takes a const Student * as a parameter for each 
// element in the void * array. Hint: you will need to cast void * elements to type Student * prior to making 
// certain assignments and function calls.

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

// function prototypes -- first two are artifacts from previous chapter's solution
void Print(string, string, string, float = 4.0);
void Print(string, float);
void Print(Student);
void Print(const Student *);
void ReadData(Student *);

int main()
{
    Student *all[MAX] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    for (int i = 0; i < MAX; i++)
    {
        all[i] = new Student;
        ReadData(all[i]);
        if (i % 2)             // alternate every other Student to call one version of Print or the other
            Print(all[i]);     // call Print(const Student *) version
        else
            Print(*(all[i]));  // call Print(Student) version
    }

    void *all2[MAX] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    for (int i = 0; i < MAX; i++)
    {
        all2[i] = all[i];
        Print((Student *) all2[i]);
    }

    // remember to release memory, but just once!
    // we have two pointers to each instance; do not delete the same memory through both sets of pointers! 
    for (int i = 0; i < MAX; i++)
        delete all[i];  

    return 0;
}

void Print(string fn, string ln, string course, float gpa)
{
    cout << fn << " " << ln << " is taking " << course;
    cout << " and has a gpa of " << std::setprecision(3) << gpa << endl;
}

void Print(string ln, float gpa)
{
    cout << ln << " has gpa of " << std::setprecision(3) << gpa << endl;
}

void Print(Student s)
{
    cout << "void Print(Student)" << endl;
    cout << s.firstName << " " << s.lastName << " is taking " << s.course;
    cout << " and has a gpa of " << std::setprecision(3) << s.gpa << endl;
}

void Print(const Student *s)
{
    cout << "void Print(const Student *)" << endl;
    cout << s->firstName << " " << s->lastName << " is taking " << s->course;
    cout << " and has a gpa of " << std::setprecision(3) << s->gpa << endl;
}

void ReadData(Student *s)
{
    cout << "Please enter <firstname> <lastname>: ";
    cin >> s->firstName >> s->lastName;
    cout << "Please enter " << s->firstName << " " << s->lastName;
    cout << "'s <gpa> and <course>: ";
    cin >> s->gpa >> s->course;
}

