// (c) 2020 Dorothy R. Kirk.  All Rights Reserved.
// Purpose: Illustrate optional names for arguments in function prototype

#include <iostream>
 
using std::cout;   // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int minimum(int arg1, int arg2);   // function prototype with optional argument names


int main()
{
    int x = 5;
    int y = 89;
    cout << minimum(x, y) << endl;  // function call with actual parameters

    return 0;
}

[[nodiscard]] int minimum(int a, int b)  // function definition with formal parameters
{
    if (a < b)
        return a;
    else
        return b;
}
