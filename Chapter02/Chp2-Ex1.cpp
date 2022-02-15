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

const int MAX = 50;  // simple const variable declaration and initialization

constexpr int LARGEST = 50;  // simple constexpr variable declaration and initialization
 
constexpr int Minimum(int a, int b)   // function's return value is a constexpr
{
    return (a < b) ? a : b;
}

int main()
{
    int x = 0, y = 0;
    constexpr int a = 10, b = 15;   // note: const applies to both a and b; note: variables not being used in
                                    // same sense as a #define, so not capitalized here out of convention 
    cout << "Enter two <int> values: ";
    cin >> x >> y;
    const int min = Minimum(x, y);  // const variable initialized with a function's return value
    cout << "Minimum is: " << min << endl;

    constexpr int smallest = Minimum(a, b);  // constexpr variable initialized with return value of constexpr fn
    cout << "Smallest of " << a << " " << b << " is: " << smallest << endl;
 
    char bigName[MAX] = {""};   // const variable used to size an array
    char largeName[LARGEST] = {""};  // constexpr used to size an array
    cout << "Enter two names: ";
    cin >> setw(MAX) >> bigName >> setw(LARGEST) >> largeName;
    const int namelen = strlen(bigName);   // a const can be initialized with a calculated value
    cout << "Length of name 1: " << namelen << endl;
    cout << "Length of name 2: " << strlen(largeName) << endl;

    return 0;
}

