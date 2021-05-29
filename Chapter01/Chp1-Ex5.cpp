// (c) Dorothy R. Kirk.  All Rights Reserved.
// Purpose: Review simple looping with for loops

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::endl;

int main()
{
    int i;   // though we'll prefer to declare i within the loop to limit its scope to the loop only 
             // (and will do so ever after), this example is paired with the book to discuss the scope of 
             // i when it is declared outside of the loop as a cautionary warning. 
             // It is compared to j's scope below. 
    
    for (i = 0; i < 10; i++)
        cout << i << endl;

    for (int j = 0; j < 10; j++)    // preferred declaration of loop control variable within loop
        cout << j << endl;

	
    return 0;
}

