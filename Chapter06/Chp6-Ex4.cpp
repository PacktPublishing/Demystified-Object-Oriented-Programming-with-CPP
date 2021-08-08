// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate protected inheritance versus public inheritance

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

   void InsertBeforeItem(Item *, Item *);
   LinkListElement *RemoveSpecificItem(Item *);
   void DeleteSpecificItem(Item *);

   void InsertAtEnd(Item *);
   LinkListElement *RemoveAtEnd();
   void DeleteAtEnd();

   int IsEmpty() const { return head == nullptr; } 
   void Print();  
};

// User supplied default constructor is not necessary due to in-class initialization. 
// Here is what it would look like (or use mbr init list) if you opted not to include in-class initialization
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

void LinkList::InsertBeforeItem(Item *newItem, Item *existing)
{
   LinkListElement *temp = nullptr, *toAdd = nullptr;
   // assumes item to insert before exists
   current = head;
   if (*(static_cast<Item *>(current->GetData())) == *existing)
       InsertAtFront(newItem);
   else
   {
      while (*(static_cast<Item *>(current->GetData())) != *existing)
      {
         temp = current;
         current = current->GetNext();
      }
       
      toAdd = new LinkListElement(newItem);  // wrap an item in a LinkListElement
      temp->SetNext(toAdd);
      toAdd->SetNext(current); 
   }
}

LinkListElement *LinkList::RemoveSpecificItem(Item *item)
{
   // add implementation
}

void LinkList::DeleteSpecificItem(Item *item)
{
   // add implementation
}

void LinkList::InsertAtEnd(Item *item)
{
   if (!head)
   {
      head = new LinkListElement(item);  // constructor also nulls out next
      tail = head;
   }
   else
   {
      tail->SetNext(new LinkListElement(item));
      tail = tail->GetNext();
   }
}

LinkListElement *LinkList::RemoveAtEnd()
{
   // add implementation
}

void LinkList::DeleteAtEnd()
{
   // add implementation
}

void LinkList::Print()
{
   if (!head)
      cout << "<EMPTY>";
   current = head;
   while (current)
   {
      Item output;  // localize temp output var
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

class Queue : protected LinkList
{
private:
   // no new data members are necessary
public:
   // Constructor prototype shown below is not needed; we get default without prorotype (since there are no other ctors)
   // Shown in comments to show optional use of =default to get default ctor
   // Queue() = default;   // will call LinkList() constructor 
   // Destructor prototype is needed (per virtual keyword)
   virtual ~Queue() = default; // we'll discuss virtual in Chp 7 
   // Here, we specify the pubilc interface which Queue instances may utilize.
   // With protected inheritance, the protected and public members inherited 
   // from LinkList act as though they were defined by Queue as protected 
   // (i.e. and are now ONLY accessible through the scope of Queue and
   // through the scope of descendants of Queue).   
   void Enqueue(Item *i) { InsertAtEnd(i); }
   Item *Dequeue(); 
   // It is necessary to redefine these operations--LinkList is a protected base class
   int IsEmpty() const { return LinkList::IsEmpty(); }
   void Print() { LinkList::Print(); }
};

Item *Queue::Dequeue()
{
   LinkListElement *front;
   front = RemoveAtFront();
   Item *item = new Item(*(static_cast<Item *>(front->GetData()))); // make copy of front's data
   delete front; 
   return item;
}


class PriorityQueue : public Queue
{
private:
   // no new data members are necessary
public:
   // Constructor prototype shown below is not needed; we get default without prorotype (since there are no other ctors)
   // Shown in comments to show optional use of =default to get default ctor
   // PriorityQueue() = default;   // will call Queue() default constructor 
   // Destructor prototype is needed (per virtual/override)
   ~PriorityQueue() override = default; // we'll discuss override in Chp 7
   // Here, we specify the pubilc interface which PriorityQueue instances may utilize.
   // Since we are inherited from Queue publicly, we inherit the public interface
   // from Queue.  Since Queue is inherited protectedly from LinkList, the public
   // interface from LinkList which is considered protected to Queue is also considered
   // protected to PriorityQueue, so these operations are available within the scope
   // of PriorityQueue.  Note that these operations would not be available within the
   // scope of PriorityQueue if Queue were inherited privately from LinkList.

   void PriorityEnqueue(Item *i1, Item *i2) { InsertBeforeItem(i1, i2); }
};

int main()
{
   Queue q1;

   q1.Enqueue(new Item(50));
   q1.Enqueue(new Item(67));
   q1.Enqueue(new Item(80));
   q1.Print();

   while (!(q1.IsEmpty()))
   {
      q1.Dequeue();
      q1.Print();
   }

   PriorityQueue q2;

   Item *item = new Item(167);
   q2.Enqueue(new Item(67));
   q2.Enqueue(item);
   q2.Enqueue(new Item(180));
   q2.PriorityEnqueue(new Item(100), item); // add new item before existing one

   q2.Print();

   while (!(q2.IsEmpty()))
   {
      q2.Dequeue();
      q2.Print();
   }

   return 0;
}
