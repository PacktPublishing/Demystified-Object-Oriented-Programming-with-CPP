// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Dynamically allocated 2-D array - using an array of pointers

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;   
using std::endl;
using std::flush;

constexpr int NUMROWS = 5;

int main()
{
    // float *TwoDimArray[NUMROWS];   // caution - this array is uninitialized, so the following declaration is preferrred
    float *TwoDimArray[NUMROWS] = {nullptr, nullptr, nullptr, nullptr, nullptr};   // alternatively, initialize each element to nullptr
    int numColumns = 0;

    cout << "Enter number of columns: " << flush;
    cin >> numColumns;

    for (int i = 0; i < NUMROWS; i++)
    {
        // allocate column quantity for each row
        TwoDimArray[i] = new float[numColumns];

        // load each column entry with dta
        for (int j = 0; j < numColumns; j++)
        {
            TwoDimArray[i][j] = i + j + .05;
            cout << TwoDimArray[i][j] << " ";

        }
        cout << endl;
    }

    for (int i = 0; i < NUMROWS; i++)
        delete [] TwoDimArray[i];   // delete column quantities for each row
                                    // note: delete TwoDimArray[i]; would also work since this is of a standard type
                                    // (the []'s ensure a clean up fn is called on each element -- useful for user defined types)
                                    // more on that when we talk about classes in detail in Chapter 5

    return 0;
}
