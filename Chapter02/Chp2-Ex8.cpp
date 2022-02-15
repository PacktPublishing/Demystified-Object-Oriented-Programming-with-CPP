// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review simple type conversion 

#include <iostream>

using std::cout;  // preferred to: using namespace std;
using std::endl;

[[nodiscard]] int Maximum (int, int);        // overloaded fn prototypes. 
[[nodiscard]] float Maximum (float, float);  // Return type is not part of the signature

int main()
{
    char a = 'A', b = 'B';
    float x = 5.7, y = 9.89;
    int m = 6, n = 10;

    cout << "The maximum is: " << Maximum(a, b) << endl; 
    cout << "The maximum is: " << Maximum(x, y) << endl; 
    cout << "The maximum is: " << Maximum(m, n) << endl; 
    // Note: the following line would generate a compiler error since
    // there are two equally good candidates -- hence "ambiguous"
    // cout << "The maximum is: " << Maximum(a, y) << endl; 
    // We can force a choice through using an explicit typecast
    cout << "The maximum is: " << Maximum(static_cast<float>(a), y) << endl; 
	
    return 0;
}

[[nodiscard]] int Maximum (int arg1, int arg2)
{
    if (arg1 > arg2)
        return arg1;
    else
        return arg2;
}

[[nodiscard]] float Maximum (float arg1, float arg2)
{
    if (arg1 > arg2)
        return arg1;
    else
        return arg2;
}
