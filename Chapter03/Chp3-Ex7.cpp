// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates a pointer as a return type from a function
// Let's try not to get worked up that a char * is demonstrated. This is a chapter about pointers! 
// You'll need to have some facility using a char * on occasion, even if we prefer a string most elsewhere.

#include <iostream>
#include <iomanip>

using std::cin;   // preferred to: using namespace std;
using std::cout;
using std::endl; 
using std::flush; 
using std::setw; 

constexpr int MAX = 20;

[[nodiscard]] char *createName();  // function prototype

int main()    
{
   char *name = nullptr;
   name = createName();
   cout << "Name: " << name << endl;
   delete [] name;   // notice that we delete in a different scope than that which we allocated. 
                     // this is a motivation for us later choosing a smart pointer (to alleviate unintentional errors)
   return 0;         // Also note that delete name; would have been ok (primitive type)
}

[[nodiscard]] char *createName()
{
   char *temp = new char[MAX];
   cout << "Enter name: " << flush;
   cin >> setw(MAX) >> temp;   // setw ensures we don't overflow the input buffer 
   return temp;
}
