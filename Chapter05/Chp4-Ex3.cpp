// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose:  Illustrates the difference between function arguments 
//           which are pointers and those which are references

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::flush;

void AddOne(int &);
void AddOne(int *);
void Display(int &);

int main()
{
   int x = 10, *y = nullptr;
   y = new int;
   *y = 15;
   Display(x);
   Display(*y);

   AddOne(x);   // calls reference version
   AddOne(*y);
   Display(x);
   Display(*y);

   AddOne(&x);  // calls pointer version
   AddOne(y);
   Display(x);
   Display(*y);

   delete y;

   return 0;
}

void AddOne(int &arg)
{
   arg++;
}

void AddOne(int *arg)
{
   (*arg)++;
}

void Display(int &arg)
{
   cout << arg << " " << flush;
}
