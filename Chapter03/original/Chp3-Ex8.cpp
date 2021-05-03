// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a pointer to const qualifed data as a function argument
// and as a return type from a function

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

char suffix = 'A';

const char *genId(const char *);  // function prototype

int main()    
{
   const char *newId1, *newId2;
   newId1 = genId("Group");  // fn call will allocate memory 
   newId2 = genId("Group");  // fn call will allocate memory 
   cout << "New ids: " << newId1 << " " << newId2 << endl;
   delete newId1;
   delete newId2;

   return 0;
}

const char *genId(const char *base)
{
   char *temp = new char[strlen(base) + 2]; // One extra space for suffix plus null
   strcpy(temp, base);
   temp[strlen(base)] = suffix++;  // append suffix to base
   temp[strlen(base) + 1] = '\0';  // add null character
   return temp;   // temp will be up-cast to a const char * to be treated more 
                  // restrictively than it was defined
}
