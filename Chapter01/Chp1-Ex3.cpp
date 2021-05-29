// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose: To review conditional statements

#include <iostream>

using std::cin;    // preferred to: using namespace std;
using std::cout;
using std::endl;

int main()
{
    int x = 0;     

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

