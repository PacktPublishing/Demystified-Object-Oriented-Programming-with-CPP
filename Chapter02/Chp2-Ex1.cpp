// (c) 2020 Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrate use of const qualified variables

#include <iostream>
#include <iomanip>
#include <cstring>
 
using namespace std;

// simple const variable declaration and initialization
const int MAX = 50;
 
int minimum(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    int x, y;
    cout << "Enter two values: ";
    cin >> x >> y;
    const int MIN = minimum(x, y);  // const variable initialized 
                                    // with a function's return value
    cout << "Minimum is: " << MIN << endl;
 
    char bigName[MAX];   // const variable used to size an array
    cout << "Enter a name: ";
    cin >> setw(MAX) >> bigName;
    const int NAMELEN = strlen(bigName);
    cout << "Length of name: " << NAMELEN << endl;

    return 0;
}

