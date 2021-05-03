// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Simple pointer to user-defined type example

#include <iostream>

using namespace std;

struct collection
{
    int x;
    float y;
};


int main()
{
    collection *item;   // pointer declaration

    item = new collection;  // memory allocation
    item->x = 9;  // use -> to access data member x
    (*item).y = 120.77;  // alternative notation to access member y 
    cout << (*item).x << " " << item->y << endl;

    delete item;
	
    return 0;
}

