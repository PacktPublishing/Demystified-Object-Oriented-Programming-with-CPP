// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To demonstrate a simple smart pointer class
// Note: This class still needs to decide how to handle copy constructor and assignment operator
// That is, shallow copies/assignment (probably not), deep copies/assignment (maybe), or prohibit copies/assignment (likely)
// To compile: g++ -c PersonImpl.cpp
//             g++ -c Chp20-Ex2.cpp
//             g++ -o runme PersonImpl.o Chp20-Ex2.o   (executable is in 'runme')

#include <iostream>
#include "Person.h"

using std::cout;    // preferred to: using namespace std;
using std::endl;

template <class Type>
class SmartPointer
{
private:
    Type *pointer;
public:
    SmartPointer(Type *ptr = nullptr) { pointer = ptr; }
    virtual ~SmartPointer() { cout << "SmartPtr Destructor" << endl; delete pointer; }
    Type *operator->() { return pointer; }
    Type &operator*() { return *pointer; }
};

int main()
{
    SmartPointer<int> p1(new int());
    SmartPointer<Person> pers1(new Person("Renee", "Alexander", 'K', "Dr."));

    *p1 = 100;
    cout << *p1 << endl;
    (*pers1).Print();   // or use: pers1->Print();
 
    return 0;
}

