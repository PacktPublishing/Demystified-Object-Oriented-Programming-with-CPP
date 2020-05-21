// (c) 2020 Dorothy R. Kirk. All Rights Reserved
// Purpose: To review conditional statements

#include <iostream>

using namespace std;

int main()
{
    int x;

    cout << "Enter an integer: ";
    cin >> x;

    if (x == 0)
        cout << "x is 0" << endl;
    else if (x < 0)
        cout << "x is negative" << endl;
    else
    {
        cout << "x is positive" << endl;
        cout << "and ten times x is: " << x*10 << endl;
    } 
	
    return 0;
}
