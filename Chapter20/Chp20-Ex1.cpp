// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate use of pImpl pattern 
// Note: this driver can also be used with non-pImpl Person class or pImpl with unique pointers -- works the same!

#include <iostream>
#include "Person.h"

using namespace std;

const int MAX = 3;

int main()
{
    Person *people[MAX];
    people[0] = new Person("Giselle", "LeBrun", 'R', "Ms.");   
    people[1] = new Person("Zack", "Moon", 'R', "Dr."); 
    people[2] = new Person("Gabby", "Doone", 'A', "Dr.");

    for (int i = 0; i < MAX; i++)
       people[i]->Print();

    for (int i = 0; i < MAX; i++)
       delete people[i];   

    return 0;
}

