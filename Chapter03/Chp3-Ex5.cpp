// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Dynamically allocated 3-D array - using a pointer to a pointer 

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::flush;

int main()
{
    int dim1 = 0, dim2 = 0, dim3 = 0; 
    int ***ThreeDimArray = nullptr;

    cout << "Enter dim 1, dim 2, dim 3: " << flush;
    cin >> dim1 >> dim2 >> dim3; 
    ThreeDimArray = new int ** [dim1];    // allocate dim 1

    for (int i = 0; i < dim1; i++)
    {
        ThreeDimArray[i] = new int * [dim2];  // allocate dim 2

        for (int j = 0; j < dim2; j++)
        {
            ThreeDimArray[i][j] = new int [dim3]; // allocate dim 3
            for (int k = 0; k < dim3; k++)
            {
                ThreeDimArray[i][j][k] = i + j + k;
                cout << ThreeDimArray[i][j][k] << " ";
            }
            cout << endl;

        }
        cout << endl;
    }

    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
            delete [] ThreeDimArray[i][j];   // release dim 3 
        delete [] ThreeDimArray[i];   // release dim 2 
    }
    delete [] ThreeDimArray;   // release dim 1 

    return 0;
}
