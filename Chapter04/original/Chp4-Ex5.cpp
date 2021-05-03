// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a reference to a const object 

#include <iostream>
using namespace std;

int main()    
{
   int x = 5;
   const int &refInt = x;
   cout << x << " " << refInt << endl;
   // refInt = 6;  // illegal. We can't change value of refInt
   x = 7;
   cout << x << " " << refInt << endl;

   return 0;
}

