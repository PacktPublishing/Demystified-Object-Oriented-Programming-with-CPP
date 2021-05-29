// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose: To illustrate basic iostream manipulators

#include <iostream>
#include <iomanip>

using std::cout;     // preferred to: using namespace std;
using std::cin; 
using std::endl; 
using std::flush;
using std::setw;
using std::setprecision;

int main()
{
    char name[20];   // caution; unitialized array of char
    float gpa = 0.0;
    cout << "Please enter a name and a gpa: ";
    // Now, we won't overflow the input buffer of name (by using setw) 
    cin >> setw(20) >> name >> gpa;
    cout << "Hello " << name << flush;
    cout << ". GPA is: " << setprecision(3) << gpa << endl;
    return 0;
}

