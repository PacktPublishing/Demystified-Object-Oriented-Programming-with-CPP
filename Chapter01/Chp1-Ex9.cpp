// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review simple user-defined type: class (in simplist form)

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Student
{
public:
    string name;
    float semesterGrades[5];
    float gpa;
};

int main()
{
    Student s1;
    s1.name = "George Katz";
    s1.semesterGrades[0] = 3.0;
    s1.semesterGrades[1] = 4.0;
    s1.gpa = 3.5;
	
    cout << s1.name << " has GPA: " << s1.gpa << endl; 
    return 0;
}

