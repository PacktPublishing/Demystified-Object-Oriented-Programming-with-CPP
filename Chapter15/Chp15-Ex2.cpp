// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate items to include in a driver to test a class. 
// Sample driver to test the Student class. 

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Person.h"
#include "Student.h"

using namespace std;

constexpr int MAX = 3;

int main()
{
    // Test all means for instantiation, including copy constructor
    Student s0; // Default construction

    // instantiate two Students
    Student s1("Jo", "Li", 'H', "Ms.", 3.7, "C++", "UD1234");
    Student s2("Sam", "Lo", 'A', "Mr.", 3.5, "C++", "UD2245");

    // These initializations implicitly invoke copy constructor
    Student s3(s1);
    Student s4 = s2;

    // Test the assignment operator 
    Student s5("Ren", "Ze", 'A', "Dr.", 3.8, "C++", "BU5563");
    Student s6;
    s6 = s5;  // this is an assignment, not initialization

    // Test each public method. A sample is shown here. Be sure to test ALL methods.
    s1.Print();   
    s3.Print();
    s2.Print();
    s4.Print();
   
    // Generalize derived instances as base types -- do methods work as expected?
    Person *people[MAX] { nullptr, nullptr, nullptr };
    people[0] = new Person("Juliet", "Martinez", 'M', "Ms.");   // base instance for comparison
    people[1] = new Student("Zack", "Moon", 'R', "Dr.", 3.8, "C++", "UMD1234");  // derived instances
    people[2] = new Student("Gabby", "Doone", 'A', "Dr.", 3.9, "C++", "GWU4321"); 

    for (int i = 0; i < MAX; i++)
    {
       people[i]->IsA();
       cout << "  ";
       people[i]->Print();
    } 

    // Test destruction sequence (for dynamically allocated instances)
    for (int i = 0; i < MAX; i++)
       delete people[i];   // engage virtual dest. sequence

    return 0;
}
