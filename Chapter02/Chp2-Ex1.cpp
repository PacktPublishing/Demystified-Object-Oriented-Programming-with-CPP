// (c) 2020 Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrate use of const qualified variables

#include <iostream>
#include <iomanip>
#include <cstring>   // don't worry, the cstring illustrates an eductional point, demonstrating how a const can be
                     // used to size an array. It could be an array of any type, but the char [] allows us to 
                     // illustrate two uses of const qualification. Don't worry, we'll generally use std::string.

using std::cout;     // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::setw;

// simple const variable declaration and initialization
const int MAX = 50;
 
int minimum(int a, int b)
{
    return (a < b) ? a : b;
}

int main()
{
    int x = 0, y = 0;
    cout << "Enter two <int> values: ";
    cin >> x >> y;
    const int MIN = minimum(x, y);  // const variable initialized 
                                    // with a function's return value
    cout << "Minimum is: " << MIN << endl;
 
    char bigName[MAX];   // const variable used to size an array
    cout << "Enter a name: ";
    cin >> setw(MAX) >> bigName;
    const int NAMELEN = strlen(bigName);   // a const can be initialized with a calculated value
    cout << "Length of name: " << NAMELEN << endl;

    return 0;
}

