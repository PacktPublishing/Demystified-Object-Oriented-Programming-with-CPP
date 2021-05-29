// (c) Dorothy R. Kirk. All Rights Reserved.
// Chp2, Question 2, a - d. Sample solution
// Write a small C++ program to prompt a user to enter information regarding a Student, and print out the data.
// a. Student information should minimally include first name, last name, gpa, and the current course in which 
// the Student is registered. This information may be stored in a simple class. You may utilize either char arrays 
// to represent the string fields since we have not yet covered pointers, or you may (preferably) utilize the string 
// type.  Also, you may read in this information in the main function rather than creating a separate function to 
// read in the data (since the latter will require knowledge of pointers or references). Please do not use global 
// (i.e. extern variables).
// b. Create a function to print out all the data for the Student. Remember to prototype this function. 
// Use a default value of 4.0 for gpa in the prototype of this function. Call this function two ways: once passing 
// in each argument explicitly, and once using the default gpa.
// c. Now, overload the print function with one which either prints out selected data (i.e. last name and gpa) or 
// with a version of this function which takes a Student as an argument (but not a pointer or reference to a 
// Student – we’ll do that later). Remember to protype this function.
// d. Use iostreams for I/O.

#include <iomanip>
#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::string;

class Student
{
public:
    string firstName;
    string lastName;
    float gpa;
    string course;
};

void Print(string, string, string, float = 4.0);
void Print(string, float);
void Print(Student);

int main()
{
    Student s1;
	
    cout << "Please enter <firstname> <lastname>: ";
    cin >> s1.firstName >> s1.lastName;
    cout << "Please enter " << s1.firstName << " " << s1.lastName;
    cout << "'s <gpa> and <course>: ";
    cin >> s1.gpa >> s1.course;

    Print(s1.firstName, s1.lastName, s1.course, s1.gpa);
    Print(s1.firstName, s1.lastName, s1.course);	// use default gpa
    Print(s1.lastName, s1.gpa);	// use overloaded fn.

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
    cout << s.firstName << " " << s.lastName << " is taking " << s.course;
    cout << " and has a gpa of " << std::setprecision(3) << s.gpa << endl;
}

