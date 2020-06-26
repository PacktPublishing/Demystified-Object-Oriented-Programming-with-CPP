// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose:  Illustrates the difference between function arguments 
//           which are pointers and those which are references

#include <iostream>

using namespace std;

void AddOne(int &);
void AddOne(int *);
void Display(int &);

int main()
{
   int x = 10, *y;
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
