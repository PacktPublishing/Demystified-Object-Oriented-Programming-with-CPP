// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate private inheritance versus public inheritance

#include <iostream>
using std::cout;
using std::endl;

typedef int Item;  

class LinkListElement
{
private:
   void *data = nullptr;
   LinkListElement *next = nullptr;
public:
   LinkListElement() = default; 
   LinkListElement(Item *i) : data(i), next(nullptr) { }
   ~LinkListElement() { delete static_cast<Item *>(data); next = nullptr; }
   void *GetData() { return data; }
   LinkListElement *GetNext() const { return next; }
   void SetNext(LinkListElement *e) { next = e; }
};

class LinkList
{
private:
   LinkListElement *head = nullptr;
   LinkListElement *tail = nullptr;
   LinkListElement *current = nullptr;
public:
   LinkList() = default;
   LinkList(LinkListElement *);
   ~LinkList();
   void InsertAtFront(Item *);
   LinkListElement *RemoveAtFront();
   void DeleteAtFront();
   int IsEmpty() const { return head == nullptr; } 
   void Print();  
};

// If we chose to write the default constructor ourselves (rather than use in-class initialization),
// it might look as below (or use the mbr init list)
/*
LinkList::LinkList()
{
   head = tail = current = nullptr;
}
*/

LinkList::LinkList(LinkListElement *element)
{
   head = tail = current = element;
}

void LinkList::InsertAtFront(Item *theItem)
{
   LinkListElement *newHead = new LinkListElement(theItem);

   newHead->SetNext(head);  // newHead->next = head;
   head = newHead;
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
   delete deallocate;    // destructor will delete data, set next to nullptr
}

void LinkList::Print()
{
   if (!head)
      cout << "<EMPTY>";
   current = head;
   while (current)
   {
      Item output;  // localize temp var
      output = *(static_cast<Item *>(current->GetData()));
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
   // Constructor and destructor prototypes shown below are not needed; we get both without these prototypes!
   // Since no other constructor exists, we get Stack() without any prototype. Same for destructor.
   // Shown in comments to show how optional prototyping can be done with =default
   // Stack() = default;  // will call LinkList() default ctor
   // ~Stack() = default; 

   // Here, we specify the pubilc interface which Stack instances may utilize.
   // With private inheritance, the protected and public members inherited 
   // from LinkList act as though they were defined by Stack as private
   // (i.e. and are now ONLY accessible through the scope of Stack).   
   void Push(Item *i) { InsertAtFront(i); }
   Item *Pop(); 
   // It is necessary to redefine these operations--LinkList is a private base class
   int IsEmpty() const { return LinkList::IsEmpty(); }  
   void Print() { LinkList::Print(); }
};

Item *Stack::Pop()
{
   LinkListElement *top;
   top = RemoveAtFront();   
   Item *item = new Item(*(static_cast<Item *>(top->GetData())));  // copy top's data
   delete top;
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
