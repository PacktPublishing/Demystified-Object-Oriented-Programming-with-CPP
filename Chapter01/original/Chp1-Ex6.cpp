// (c) 2020 Dorothy R. Kirk.  All Rights Reserved.
// Purpose: Review nested for loops

#include <iostream>

using namespace std;

int main()
{
    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;

        for (int j = 0; j < 10; j++)
            cout << j << endl;

        cout << "\n";
    }

	
    return 0;
}
