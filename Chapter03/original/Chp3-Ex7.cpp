// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a pointer as a return type from a function

#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 20;

char *createName();  // function prototype

int main()    
{
   char *name;
   name = createName();
   cout << "Name: " << name << endl;
   delete name;

   return 0;
}

char *createName()
{
   char *temp = new char[MAX];
   cout << "Enter name: " << flush;
   cin >> setw(MAX) >> temp;
   return temp;
}
