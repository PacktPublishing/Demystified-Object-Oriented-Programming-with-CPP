// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a reference as a return type from a function

#include <iostream>
using namespace std;

int &CreateId();  // function prototype

int main()    
{
    int &id1 = CreateId();    // reference established
    int &id2= CreateId();
    cout << "Id1: " << id1 << " Id2: " << id2 << endl;
    delete &id1;   // Here, '&' is address-of not reference
    delete &id2;

    return 0;
}

int &CreateId()
{
    static int count = 100;   // initialize with first id
    int *memory = new int;
    *memory = count++;    // use count as id, then increment
    return *memory;
}
