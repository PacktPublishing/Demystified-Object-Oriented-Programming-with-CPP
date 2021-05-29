// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate private inheritance versus public inheritance

#include <iostream>
using namespace std;

typedef int Item;  

class LinkListElement
{
private:
   void *data;
   LinkListElement *next;
public:
   LinkListElement() { data = 0; next = 0; }
   LinkListElement(Item *i) { data = i; next = 0; }
   ~LinkListElement() { delete (Item *) data; next = 0; }
   void *GetData() { return data; }
   LinkListElement *GetNext() { return next; }
   void SetNext(LinkListElement *e) { next = e; }
};

class LinkList
{
private:
   LinkListElement *head;
   LinkListElement *tail;
   LinkListElement *current;
public:
   LinkList();
   LinkList(LinkListElement *);
   ~LinkList();
   void InsertAtFront(Item *);
   LinkListElement *RemoveAtFront();
   void DeleteAtFront();
   int IsEmpty() { return head == 0; } 
   void Print();  
};

LinkList::LinkList()
{
   head = tail = current = 0;
}

LinkList::LinkList(LinkListElement *element)
{
   head = tail = current = element;
}

void LinkList::InsertAtFront(Item *theItem)
{
   LinkListElement *temp = new LinkListElement(theItem);

   temp->SetNext(head);  // temp->next = head;
   head = temp;
}

LinkListElement *LinkList::RemoveAtFront()
{
   LinkListElement *remove = head;
   head = head->GetNext();  // head = head->next;
   current = head;    // reset current for usage elsewhere
   return remove;    
}

void LinkList::DeleteAtFront()
{
   LinkListElement *deallocate;
   deallocate = RemoveAtFront();
   delete deallocate;    // destructor will delete data, set next to NULL
}

void LinkList::Print()
{
   Item output;

   if (!head)
      cout << "<EMPTY>";
   current = head;
   while (current)
   {
      output = *((Item *) current->GetData());
      cout << output << " ";
      current = current->GetNext();
   }
   cout << endl;
}

LinkList::~LinkList()
{
   while (!IsEmpty())
      DeleteAtFront();
}

class Stack : private LinkList
{
private:
   // no new data members are necessary
public:
   Stack() : LinkList() { }
   ~Stack() { }
   // Here, we specify the pubilc interface which Stack instances may utilize.
   // With private inheritance, the protected and public members inherited 
   // from LinkList act as though they were defined by Stack as private
   // (i.e. and are now ONLY accessible through the scope of Stack).   
   void Push(Item *i) { InsertAtFront(i); }
   Item *Pop(); 
   // It is necessary to redefine these operations--LinkList is a private base class
   int IsEmpty() { return LinkList::IsEmpty(); }  
   void Print() { LinkList::Print(); }
};

Item *Stack::Pop()
{
   LinkListElement *temp;
   temp = RemoveAtFront();
   Item *item = new Item(*((Item *) temp->GetData()));  // copy temp's data
   delete temp;
   return item;
}

int main()
{
   Stack stack1;  // create a stack
 
   // Add some items to the stack.  Notice that we may only utilize the public      
   // interface provided by Stack to add items--to instances of stack, the public
   // interface of LinkList acts as though it is private to Stack, and hence not
   // accessible from the scope of main.
   stack1.Push(new Item (3000)); 
   stack1.Push(new Item (600));
   stack1.Push(new Item (475));

   cout << "Stack 1: ";
   stack1.Print();

   // pop elements from stack, one by one
   while (!(stack1.IsEmpty()))
   {
      stack1.Pop();
      cout << "Stack 1 after popping an item: ";
      stack1.Print();
   }

   return 0;
}
