// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a pointer to const qualifed data as a function argument
// and as a return type from a function
// Note: A const char * is used here for educational purposes (this is a chapter featuring pointers).
// Not to worry, we'll use a string whenever possible, but we're trying to illustrate a pointer concept right now.

#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout;    // preferred to: using namespace std;
using std::endl;

char suffix = 'A';

const char *genId(const char *);  // function prototype

int main()    
{
   const char *newId1 = nullptr, *newId2 = nullptr;
   newId1 = genId("Group");  // fn call will allocate memory 
   newId2 = genId("Group");  // fn call will allocate memory 
   cout << "New ids: " << newId1 << " " << newId2 << endl;
   delete [] newId1;   // notice that we are deallocating in a different scope than we allocated.
   delete [] newId2;   // this will give us motivation later to use a smart pointer for safety.
                       // note: delete newId1; or delete newId2; would also be ok (primitive type)

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
