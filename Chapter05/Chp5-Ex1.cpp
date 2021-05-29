// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose: To demonstrate a class and struct with simple member functions

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::string;

struct student
{
    string name;
    float gpa;
    void Initialize(string, float);  // function prototype
    void Print();
};

class University
{
public:
    string name;
    int numStudents;
    void Initialize(string, int);   // function prototype
    void Print();
};

void student::Initialize(string n, float avg)
{ 
    name = n;    // we'll see how to initialize this, rather than use assignment, later in this chapter
    gpa = avg;
}

void student::Print()
{ 
    cout << name << " GPA: "  << gpa << endl;
}

void University::Initialize(string n, int num)
{ 
    name = n;
    numStudents = num;
} 

void University::Print()
{ 
    cout << name << " Enrollment: "  << numStudents << endl;
}

int main()
{ 
    student s1;  // instantiate a student (struct instance)
    s1.Initialize("Gabby Doone", 4.4);
    s1.Print();

    University u1;  // instantiate a University (class)
    u1.Initialize("GWU", 25600);
    u1.Print();

    University *u2;         // pointer declaration
    u2 = new University();  // instantiation with new()
    u2->Initialize("UMD", 40500);  
    u2->Print();  // or alternatively: (*u2).Print();
    delete u2;  

    return 0;
}
