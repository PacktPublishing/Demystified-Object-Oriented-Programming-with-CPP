// (c) Dorothy R. Kirk.  All Rights Reserved
// Purpose: To review simple looping with while and do-while

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;

int main()
{
    int i = 0;
    
    while (i < 10)
    {
        cout << i << endl;
        i++;
    }

    i = 0;

    do
    {
        cout << i << endl;
        i++;
    } while (i < 10);

	
    return 0;
}

