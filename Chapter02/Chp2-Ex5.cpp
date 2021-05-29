// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrate prototyping in different scopes with different default values

#include <iostream>
 
using std::cout;   // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int minimum(int, int);   // standard function prototype 

void function1(int x)
{
    [[nodiscard]] int minimum(int arg1, int arg2 = 500);  // local prototype with default value
   
    cout << minimum(x) << endl;
}

void function2(int x)
{
    [[nodiscard]] int minimum(int arg1, int arg2 = 90);  // local prototype with default value
   
    cout << minimum(x) << endl;
}

[[nodiscard]] int minimum(int a, int b)  // function definition with formal parameters
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    function1(30);
    function2(450);

    return 0;
}

