// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrates references to user defined types 

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::string;

class Student      // very simple class -- we'll add to it in the next chapter
{
public:          
    string name;
    float gpa;
};

int main()
{
    Student s1;
    Student &sRef = s1;
    s1.name = "Katje Katz";
    s1.gpa = 3.75;
    cout << s1.name << " has GPA: " << s1.gpa << endl; 
    cout << sRef.name << " has GPA: " << sRef.gpa << endl; 

    sRef.name = "George Katz";
    sRef.gpa = 3.25;
    cout << s1.name << " has GPA: " << s1.gpa << endl; 
    cout << sRef.name << " has GPA: " << sRef.gpa << endl; 

    return 0;
}
