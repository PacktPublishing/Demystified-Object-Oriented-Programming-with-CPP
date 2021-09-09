// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a more complete example with template functions and classes.
//          This example modifies our previous void * LinkList/LinkListElement pair to use templates.

#include <iostream>
using std::cout;    // preferred to: using namespace std;
using std::endl;

template <class Type> class LinkList;  // forward declaration
                                     // with template preamble
template <class Type>   // template preamble for class def
class LinkListElement
{
private:
   Type *data = nullptr;   // in-class initialization
   LinkListElement *next = nullptr;
   // private access methods to be used in scope of friend 
   Type *GetData() { return data; } 
   LinkListElement *GetNext() { return next; }
   void SetNext(LinkListElement *e) { next = e; }
public:
   friend class LinkList<Type>;   
   LinkListElement() = default; 
   LinkListElement(Type *i) : data(i), next(nullptr) { }
   ~LinkListElement(){ delete data; next = nullptr;}
};

// LinkList should only be extended as a protected or private base class; it does not contain a virtual destructor. 
// It can be used as-is, or as implementation for another ADT.

template <class Type>
class LinkList
{
private:
   LinkListElement<Type> *head = nullptr, *tail = nullptr, *current = nullptr;  // in-class initialization
public:
   LinkList() = default; 
   LinkList(LinkListElement<Type> *e) { head = tail = current = e; }
   void InsertAtFront(Type *);
   LinkListElement<Type> *RemoveAtFront();  
   void DeleteAtFront()  { delete RemoveAtFront(); }
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

template <class Type>
void LinkList<Type>::InsertAtFront(Type *theItem)
{
   LinkListElement<Type> *newHead;
   newHead = new LinkListElement<Type>(theItem);
   newHead->SetNext(head);  // newHead->next = head;
   head = newHead;
}

template <class Type>
LinkListElement<Type> *LinkList<Type>::RemoveAtFront()
{
   LinkListElement<Type> *remove = head;
   head = head->GetNext();  // head = head->next;
   current = head;    // reset current for usage elsewhere
   return remove;
}
 
template <class Type>
void LinkList<Type>::Print() 
{
   if (!head)
      cout << "<EMPTY>" << endl;
   current = head;
   while (current)
   {
      Type output;   // localize the output temp variable
      output = *(current->GetData());
      cout << output << " ";
      current = current->GetNext();
   }
   cout << endl;
}

int main()
{
    LinkList<int> list1; // create a LinkList of ints
    list1.InsertAtFront(new int (3000));
    list1.InsertAtFront(new int (600));
    list1.InsertAtFront(new int (475));
    cout << "List 1: ";
    list1.Print();
    // delete elements from list, one by one
    while (!(list1.IsEmpty()))
    {
       list1.DeleteAtFront();
       cout << "List 1 after removing an item: ";
       list1.Print();
    }

    LinkList<float> list2;  // now make a LinkList of floats
    list2.InsertAtFront(new float(30.50));
    list2.InsertAtFront(new float (60.89));
    list2.InsertAtFront(new float (45.93));
    cout << "List 2: ";
    list2.Print();

    return 0;
}

