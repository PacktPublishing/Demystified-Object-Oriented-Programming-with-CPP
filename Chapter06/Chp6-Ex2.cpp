// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate a simple encapsulated LinkList. 

#include <iostream>
using std::cout;
using std::endl;

using Item = int;  

class LinkListElement
{
private:
   void *data = nullptr;   // in-class initialization
   LinkListElement *next = nullptr;
public:
   LinkListElement() = default;   // yes, we do desire the default constructor interface
   LinkListElement(Item *i) : data(i), next(nullptr) { }
   ~LinkListElement() { delete static_cast<Item *>(data); next = nullptr; }
   void *GetData() { return data; }
   LinkListElement *GetNext() const { return next; }
   void SetNext(LinkListElement *e) { next = e; }
};

class LinkList
{
private:
   LinkListElement *head = nullptr;   // use in-class initialization
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

// If we chose to write the default constructor (versus in-class initialization), it might look like this (or use mbr init list)
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
   LinkListElement *deallocate = nullptr;
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
      Item output;  // localize the output temporary variable
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
