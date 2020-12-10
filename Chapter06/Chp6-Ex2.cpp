// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate a simple encapsulated LinkList. 

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

int main()
{
   // Create a few items, which will later be data for LinkListElements
   Item *item1 = new Item;
   *item1 = 100;
   Item *item2 = new Item(200);

   // create an element for the Linked List
   LinkListElement *element1 = new LinkListElement(item1);

   // create a linked list and initialize with one node (element)
   LinkList list1(element1);
   
   // Add some new items to the list
   list1.InsertAtFront(item2);   
   list1.InsertAtFront(new Item(50));   // add a nameless item to the list

   cout << "List 1: ";
   list1.Print();                // print out contents of list

   // delete elements from list, one by one
   while (!(list1.IsEmpty()))
   {
      list1.DeleteAtFront();
      cout << "List 1 after removing an item: ";
      list1.Print();
   }

   // create a second linked list, add some items and print
   LinkList list2;
   list2.InsertAtFront(new Item (3000));
   list2.InsertAtFront(new Item (600));
   list2.InsertAtFront(new Item (475));

   cout << "List 2: ";
   list2.Print();

   // delete elements from list, one by one
   while (!(list2.IsEmpty()))
   {
      list2.DeleteAtFront();
      cout << "List 2 after removing an item: ";
      list2.Print();
   }

   return 0;
}
