// (c) Dorothy R.  Kirk. All Rights Reserved.
// Purpose: To illustrate a class destructor.

#include <iostream>  
#include <cstring> 
using namespace std;

class University
{
private:
    char *name;
    int numStudents;
public: 
    // constructor prototypes
    University(); // default constructor
    University(const char *, int);  // alternate constructor
    University(const University &);  // copy constructor
    ~University();  // destructor prototype
    void Print();
};

University::University()  // default constructor
{
    name = 0;  // NULL pointer
    numStudents = 0;
}

University::University(const char * n, int num)  // alt constructor
{
    name = new char [strlen(n) + 1];
    strcpy(name, n);
    numStudents = num;
}

University::University(const University &u) // copy const
{
    name = new char [strlen(u.name) + 1];  // deep copy
    strcpy(name, u.name);
    numStudents = u.numStudents;
}

University::~University()  // destructor definition
{
    delete name;
    cout << "Destructor called " << this << endl;
}

void University::Print()
{
    cout << "University: " << name;
    cout << " Enrollment: " << numStudents << endl;
}

int main()
{
    University u1("Temple University", 39500);
    University *u2 = new University("Boston U", 32500);
    u1.Print();
    u2->Print();
    delete u2;   // destructor will be called before delete()
                 // destructor for u1 will be called before
    return 0;    // program completes 
}

