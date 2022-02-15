// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrate prototyping in different scopes with different default values

#include <iostream>
 
using std::cout;   // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int Minimum(int, int);   // standard function prototype 

void Function1(int x)
{
    [[nodiscard]] int Minimum(int arg1, int arg2 = 500);  // local prototype with default value
   
    cout << Minimum(x) << endl;
}

void Function2(int x)
{
    [[nodiscard]] int Minimum(int arg1, int arg2 = 90);  // local prototype with default value
   
    cout << Minimum(x) << endl;
}

[[nodiscard]] int Minimum(int a, int b)  // function definition with formal parameters
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    Function1(30);
    Function2(450);

    return 0;
}

