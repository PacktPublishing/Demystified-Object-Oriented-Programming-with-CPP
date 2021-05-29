// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Dynamically allocating single dimension array

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::flush;

struct collection
{
    int x;
    float y;
};


int main()
{
    int numElements = 0, *intArray = nullptr;  // int and pointer declaration with initializations
    collection *collectionArray = nullptr;   // pointer declaration and initialization

    cout << "How many elements would you like? " << flush;
    cin >> numElements;

    intArray = new int[numElements];
    collectionArray = new collection[numElements];

    for (int i = 0; i < numElements; i++)
    {
        intArray[i] = i;               // load each array with values 
        collectionArray[i].x = i;      // using arrray notation []
        collectionArray[i].y = i + .5;
   
        // alternatively use pointer notation to print values
        cout << *(intArray + i) << " ";
        cout << (*(collectionArray + i)).y << endl;
    }

    // mark memory for deletion
    delete [] intArray;          // for an array of primitive types, delete intArray; is also ok 
    delete [] collectionArray;   // the []'s on delete first call a 'cleanup' function on each element before reclaiming
                                 // the heap memory (useful for user defined types)-- more on that with Chapter 5

    return 0;
}
