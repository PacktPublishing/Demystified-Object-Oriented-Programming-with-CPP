// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Dynamically allocated 2-D array - using a pointer to a pointer 

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::flush;

int main()
{
    int numRows = 0, numColumns = 0;
    float **TwoDimArray = nullptr;

    cout << "Enter number of rows: " << flush;
    cin >> numRows;
    TwoDimArray = new float * [numRows];    // allocate row pointers

    cout << "Enter number of columns: " << flush;
    cin >> numColumns;

    for (int i = 0; i < numRows; i++)
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

    for (int i = 0; i < numRows; i++)
        delete [] TwoDimArray[i];   // delete columns for each row  -- note: delete TwoDimArray[i]; is also ok since primitive type      
    delete [] TwoDimArray;   // delete allocated rows  -- note: delete TwoDimAray; also ok since primitive type

    return 0;
}
