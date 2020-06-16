// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Dynamically allocated 2-D array - using an array of pointers

#include <iostream>

using namespace std;

const int NUMROWS = 5;

int main()
{
    float *TwoDimArray[NUMROWS];
    int numColumns;

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
        delete TwoDimArray[i];   // delete column for each row

    return 0;
}
