// (c) 2020 Dorothy R. Kirk. All Rights Reserved
// Purpose: To illustrate basic iostream manipulators

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    char name[20];
    float gpa;
    cout << "Please enter a name and a gpa: ";
    cin >> setw(20) >> name >> gpa;
    cout << "Hello " << name << flush;
    cout << ". GPA is: " << setprecision(3) << gpa << endl;
    return 0;
}
