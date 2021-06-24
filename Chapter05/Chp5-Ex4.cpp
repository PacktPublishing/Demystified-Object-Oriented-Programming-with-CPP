// (C) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To understand constructor basics.

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class University
{
private:
    string name;
    int numStudents;
public: 
    // constructor prototypes
    University(); // default constructor
    University(const string &, int);
    void Print();
    void CleanUp();
};

University::University()    // default, no-argument constructor
{
    // Because a string is a class type, all strings are constructed with an empty value by default. 
    // For that reason, we do not need to explicitly initialize strings if an empty string is desired. 
    // We’ll see a preferred manner of initialization for all data members shortly in this chapter.    
    // Hence, name is constructed by default (empty string)
    numStudents = 0;
}

University::University(const string &n, int num)  // alternate constructor
{
    // any pointer data members would need to be allocated here
    name = n;   // not to worry, assignment with strings will do a deep assignment
    numStudents = num;
}

void University::Print()
{
    cout << "University: " << name;
    cout << " Enrollment: " << numStudents << endl;
}

void University::CleanUp()
{
    // any pointer data members would need to be deallocated here
}

int main()
{
    University u1; // Implicit call to default constructor
    University u2("University of Delaware", 23800);  // uses alternate constructor
    University u3{"Temple University", 20500};  // also uses alternate constructor - note use of {}'s
    u1.Print();
    u2.Print();
    u3.Print();
    u1.CleanUp();
    u2.CleanUp();
    u3.CleanUp();

    return 0;
}

