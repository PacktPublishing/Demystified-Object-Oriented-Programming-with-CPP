// Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates use of using a reference to a constant object
//           as an argument to a function

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;


class Collection
{
public:
   int x;         // don't worry, we'll soon see (Chp 5) how to initialize class members easily
   float y;
};

void Update(Collection *);
void Print(const Collection &);

int main()
{
   Collection collect1, *collect2 = nullptr; 

   // allocate memory for collect2 from the heap
   collect2 = new Collection;  

   Update(&collect1);
   Update(collect2);

   Print(collect1);  
   Print(*collect2);

   // delete collection pointed to by collect2
   delete collect2;  

   return 0;
}

void Update(Collection *c)
{
   cout << "Enter <int> and <float> members: ";
   cin >> c->x >> c->y;
}
    
void Print(const Collection &c)
{
   cout << "x member: " << c.x << "   y member: " << c.y << endl;
}

