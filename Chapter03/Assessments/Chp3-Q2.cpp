// (c) Dorothy R. Kirk. All Rights Reserved.
// Chapter 3, Question 2 - sample solution
 
// Write the following pointer declarations which include a const qualification:
// a. Write a declaration for a pointer to a constant object. Assume the object is of type Student. 
// Hint: read your declaration from right to left to verify correctness.
// b. Write a declaration for a constant pointer to a non-constant object. Again, assume the object is of type Student.
// c. Write a declaration for a constant pointer to a constant object. The object will again be of type Student.

#include <iostream>

using std::string;

class Student
{
public:
    string name;
};

int main()
{
    Student *s0 = new Student;
    const Student *s1;
    Student *const s2 = s0;
    const Student *const s3 = s0;
    return 0;
}

