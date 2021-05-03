// Dorothy R. Kirk. All Rights Reserved.
// Purpose:  Illustrates use of using a reference to a constant object
//           as an argument to a function

#include <iostream>

using namespace std;


class Collection
{
public:
   int x;
   float y;
};

void Update(Collection *);
void Print(const Collection &);

int main()
{
   Collection collect1, *collect2; 

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
   cout << "Enter x and y members: ";
   cin >> c->x >> c->y;
}
    
void Print(const Collection &c)
{
   cout << "x member: " << c.x << "   y member: " << c.y << endl;
}

