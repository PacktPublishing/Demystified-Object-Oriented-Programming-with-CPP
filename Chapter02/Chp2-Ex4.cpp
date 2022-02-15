// (c) 2020 Dorothy R. Kirk. All Rights Reserved.
// Purpose: Illustrate default value usage in a function prototype

#include <iostream>
 
using std::cout;   // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int Minimum(int arg1, int arg2 = 100000);   // function prototype 
                                                          // with one default value 

int main()
{
    int x = 5;
    int y = 89;
    cout << Minimum(x) << endl;  // function call with only one argument 
                                    // (i.e. uses default  value) 
    cout << Minimum(x, y) << endl;  // no default values used 

    return 0;
}

[[nodiscard]] int Minimum(int a, int b)  // function definition with formal parameters
{
    if (a < b)
        return a;
    else
        return b;
}
