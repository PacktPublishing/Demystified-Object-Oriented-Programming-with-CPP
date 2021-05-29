// (c) Dorothy R. Kirk.  All Rights Reserved.
// Purpose: Review nested for loops

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;

int main()
{
    for (int i = 0; i < 10; i++)    // Notice our preferred declaration of i within the loop construct
    {
        cout << i << endl;

        for (int j = 0; j < 10; j++)
            cout << j << endl;

        cout << "\n";
    }

	
    return 0;
}

