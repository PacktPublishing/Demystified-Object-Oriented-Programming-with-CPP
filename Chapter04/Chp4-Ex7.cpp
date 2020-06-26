// (c) Dorothy R. Kirk.  All Rights Reserved.
// Purpose: To illustrate a reference to a pointer to data

#include <iostream>

using namespace std;

int main()
{
    int *ptr = new int;
    *ptr = 20;
    int *&refPtr = ptr;   // establish a reference to a pointer
    cout << *ptr << " " << *refPtr << endl;
    
    return 0;
}

