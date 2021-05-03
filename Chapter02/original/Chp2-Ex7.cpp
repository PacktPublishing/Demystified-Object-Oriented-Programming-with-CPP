// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review simple type conversion 

#include <iostream>

using namespace std;

int maximum (double, double);

int main()
{
    int result;
    int m = 6, n = 10;
    float x = 5.7, y = 9.89;

    result = maximum(x, y);
    cout << "Result is: " << result << endl;
    cout << "The maximum is: " << maximum(m, n) << endl; 
	
    return 0;
}

int maximum (double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}
