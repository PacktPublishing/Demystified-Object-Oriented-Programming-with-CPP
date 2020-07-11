// (C) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To understand constructor basics.

#include <iostream>
#include <cstring>
using namespace std;

class University
{
private:
    char name[30];
    int numStudents;
public: 
    // constructor prototypes
    University(); // default constructor
    University(const char *, int);
    void Print();
};

University::University()    // default, no-argument constructor
{
    name[0] = '\0';
    numStudents = 0;
}

University::University(const char * n, int num)  // alternate constructor
{
    strcpy(name, n);
    numStudents = num;
}

void University::Print()
{
    cout << "University: " << name;
    cout << " Enrollment: " << numStudents << endl;
}

int main()
{
    University u1; // Implicit call to default constructor
    University u2("University of Delaware", 23800);  // uses alternate constructor
    u1.Print();
    u2.Print();

    return 0;
}

