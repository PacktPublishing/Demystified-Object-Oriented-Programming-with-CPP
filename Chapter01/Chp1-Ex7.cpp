// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review a simple function

#include <iostream>

using std::cin;    // preferred to: using namespace std;
using std::cout;
using std::endl;

int minimum (int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    int x = 0, y = 0;

    cout << "Enter two integers: ";
    cin >> x >> y;
    cout << "The minimum is: " << minimum(x, y) << endl; 
	
    return 0;
}

