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

constexpr int largest = 50;  // simple constexpr variable declaration and initialization
 
constexpr int minimum(int a, int b)   // function's return value is a constexpr
{
    return (a < b) ? a : b;
}

int main()
{
    int x = 0, y = 0;
    constexpr int a = 10, b = 15;   
    cout << "Enter two <int> values: ";
    cin >> x >> y;
    const int MIN = minimum(x, y);  // const variable initialized with a function's return value
    cout << "Minimum is: " << MIN << endl;

    constexpr int smallest = minimum(a, b);  // constexpr variable initialized with return value of constexpr fn, 
                                             // but values in fn parameters are literals 
    cout << "Smallest of " << a << " " << b << " is: " << smallest << endl;
 
    char bigName[MAX] = {""};   // const variable used to size an array
    char largeName[largest] = {""};  // constexpr used to size an array
    cout << "Enter two names: ";
    cin >> setw(MAX) >> bigName >> setw(largest) >> largeName;
    const int NAMELEN = strlen(bigName);   // a const can be initialized with a calculated value
    cout << "Length of name 1: " << NAMELEN << endl;
    cout << "Length of name 2: " << strlen(largeName) << endl;

    return 0;
}

