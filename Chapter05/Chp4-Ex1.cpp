// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates references to objects

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::endl;

int main()
{
   int x = 10;
   int *p = new int;

   *p = 20;
  
   // References must be initialized to the object they are referencing
   // and may never be assigned another object to reference.
   // The reference and the referenced object must be the same type. 
   int &refInt1 = x;  // reference to an integer
   int &refInt2 = *p; // also a reference to an integer

   cout << x << " " << *p << " " << refInt1 << " " << refInt2 << endl;

   x++;      // updates x and refInt1
   (*p)++;   // updates *p and refInt2 

   cout << x << " " << *p << " " << refInt1 << " " << refInt2 << endl;

   refInt1++;    // updates refInt1 and x
   refInt2++;    // updates refInt2 and *p

   cout << x << " " << *p << " " << refInt1 << " " << refInt2 << endl;

   delete p;

   return 0;
}
