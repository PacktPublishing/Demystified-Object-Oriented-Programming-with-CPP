// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a reference as a return type from a function
// Note: This is certainly not a typical use, but demonstrates a reference as a return type from a function.
// (we will see this most heavily used with operator overloading so that operators can be cascaded in usage -- 
//  this is actually the original motivating reason references were added, long ago, to C++).

#include <iostream>
using std::cout;   // preferred to: using namespace std;
using std::endl;

int &CreateId();  // function prototype

int main()    
{
    int &id1 = CreateId();    // reference established
    int &id2= CreateId();
    cout << "Id1: " << id1 << " Id2: " << id2 << endl;
    delete &id1;   // Here, '&' is address-of not reference
    delete &id2;   // It is very unusual we'd delete in this fashion, but now you know you can take the address of a ref variable 
                   // Also, allocating and deleting in diff scopes can lead to errors. This will motivate use of smart pointers later
    return 0;
}

int &CreateId()
{
    static int count = 100;   // initialize with first id
    int *memory = new int;
    *memory = count++;    // use count as id, then increment
    return *memory;
}

