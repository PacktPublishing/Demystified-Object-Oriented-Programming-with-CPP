// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose: To illustrate void pointers

#include <iostream>

using namespace std;

int main()
{
    void *unspecified;  // the void * may point to any data type
    int *x;

    unspecified = new int;  // the void * now points to an int

    // the void * must be vase to an int * before it is dereferenced
    *((int *) unspecified) = 89;

    // let x point to the memory which unspecified points to
    x = (int *) unspecified;

    cout << *x << " " << *((int *) unspecified) << endl;


    return 0;
}
