// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrates references to user defined types 

#include <iostream>
#include <cstring>

using namespace std;

class Student
{
public:
    char name[20];
    float gpa;
};

int main()
{
    Student s1;
    Student &sRef = s1;
    strcpy(s1.name, "Katje Katz");
    s1.gpa = 3.75;
    cout << s1.name << " has GPA: " << s1.gpa << endl; 
    cout << sRef.name << " has GPA: " << sRef.gpa << endl; 

    strcpy(sRef.name, "George Katz");
    sRef.gpa = 3.25;
    cout << s1.name << " has GPA: " << s1.gpa << endl; 
    cout << sRef.name << " has GPA: " << sRef.gpa << endl; 

    return 0;
}
