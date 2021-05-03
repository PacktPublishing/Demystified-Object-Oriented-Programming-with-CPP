// (c) 2020 Dorothy R. Kirk. All Rights Reserved.
// Purpose: Demonstrate simple function prototyping

#include <iostream>
 
using std::cout;   // preferred to: using namespace std;
using std::endl;

int minimum(int, int);   // function prototype


int main()
{
    int x = 5, y = 89;
    cout << minimum(x, y) << endl;  // function call with actual parameters

    return 0;
}

int minimum(int a, int b)  // function definition with formal parameters
{
    if (a < b)
        return a;
    else
        return b;
}
