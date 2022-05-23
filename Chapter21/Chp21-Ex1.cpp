// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Brief demo of a unique pointer

#include <iostream>
#include <memory>
#include "Person.h"

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::unique_ptr;
using std::make_unique;

int main()
{
    unique_ptr<int> p1(new int());
    *p1 = 100;
    cout << *p1 << endl;

    unique_ptr<Person> pers1(new Person("Renee", "Alexander", 'K', "Dr."));
    (*pers1).Print(); // or alternatively use: pers1->Print();

    unique_ptr<Person> pers2;
    pers2 = move(pers1);  // take over another unique pointer's resource
    pers2->Print();

    auto pers3 = make_unique<Person>("Giselle", "LeBrun", 'R', "Ms.");
    pers3->Print();
 
    return 0;
}

