// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review a simple function

#include <iostream>

using namespace std;

int minimum (int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    int x, y;

    cout << "Enter two integers: ";
    cin >> x >> y;
    cout << "The minimum is: " << minimum(x, y) << endl; 
	
    return 0;
}
