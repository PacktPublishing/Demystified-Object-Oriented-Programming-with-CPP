// (c) 2020 Dorothy R. Kirk. All Rights Reserved.
// Purpose: Demonstrate simple function prototyping

#include <iostream>
 
using std::cout;   // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int Minimum(int, int);   // function prototype. Note optional use of 'nodiscard'


int main()
{
    int x = 5, y = 89;
    cout << Minimum(x, y) << endl;  // function call with actual parameters
    // Minimum(x, y);  // function call that ignores return value will issue a warning

    return 0;
}

[[nodiscard]] int Minimum(int a, int b)  // function definition with formal parameters
{
    if (a < b)
        return a;
    else
        return b;
}
