// (c) 2020 Dorothy R. Kirk.  All Rights Reserved
// Purpose: To review simple looping with while and do-while

#include <iostream>

using namespace std;

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
