// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a simple encapsulated LinkList, utilizing
// a friend class. A friend class is one in which all of that class's
// member functions are friend functions of the class who grants them
// friendship.  Friend functions of LinkListElement are those which 
// have access to LinkListElement members as if they were within the 
// scope of the LinkListElement class (as well as within their own 
// class scope). Friend functions are sometimes necessary for tightly
// coupled (non-related) classes, when it is otherwise inappropriate to
// universally provide selected functions in the public access region.
// Friend functions are also beneficial when used in conjunction with
// operator overloading.
// NOTE: LinkListElement and LinkList are not intended to be extended with
// public inheritance -- they do not contain virtual destructors.
// Instead, LinkList is meant to be used on its own or to serve as a 
// private or protected base class to provide the underlying implementation
// for other ADTs, such as Queue. 

#include <iostream>
using namespace std;

using Item = int;  

class LinkList;  // forward declaration

class LinkListElement
{
private:
   void *data = nullptr;    // in-class initialization
   LinkListElement *next = nullptr;

   // These member functions should not be part of the public interface
   // It is only appropriate for them to be used within the scope of LinkList,
   // who is a friend class of LinkListElement.
   void *GetData() { return data; }
   LinkListElement *GetNext() { return next; }
   void SetNext(LinkListElement *e) { next = e; }

public:
   // All member functions of LinkList are friend functions of LinkListElement 
   friend class LinkList;   
   LinkListElement() = default;  // in class init will set data and next 
   LinkListElement(Item *i) : data(i), next(nullptr) { }
   ~LinkListElement() { delete static_cast<Item *>(data); next = nullptr; }
};

class LinkList
{
private:
   LinkListElement *head = nullptr, *tail = nullptr, *current = nullptr;   // in-class initialization
public:
   LinkList() = default; 
   LinkList(LinkListElement *e) { head = tail = current = e; }
   void InsertAtFront(Item *);
   LinkListElement *RemoveAtFront();
   void DeleteAtFront() { delete RemoveAtFront(); }  // destructor will delete data, set next to NULL
   int IsEmpty() { return head == nullptr; } 
   void Print();  
   ~LinkList() { while (!IsEmpty()) DeleteAtFront(); }
};

// If we chose to write the default constructor (versus in-class initialization), it might look like this (or use mbr init list)
/*
LinkList::LinkList()
{
   head = tail = current = nullptr;
}
*/

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
 
void LinkList::Print()
{
   if (!head)
      cout << "<EMPTY>" << endl;
   current = head;
   while (current)
   {
      Item output;   // localize the output temporary variable
      output = *(static_cast<Item *>(current->GetData()));
      cout << output << " ";
      current = current->GetNext();
   }
   cout << endl;
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

