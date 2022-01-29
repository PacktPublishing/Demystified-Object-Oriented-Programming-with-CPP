// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a simple Adapter class, using private inheritance between Adapter and Adaptee.

#include <iostream>
#include <list>

using std::cout;    // preferable to: using namespace std;
using std::endl;
using std::string;
using std::list;

// Person is the Adaptee class (the class requiring an adaptation)
class Person
{
private: 
   string firstName;
   string lastName;
   char middleInitial = '\0';  // in-class initialization -- value to be used in default constructor
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
   string greeting;
protected:
   void ModifyTitle(const string &);  // Make this operation available to derived classes
public:
   Person() = default;   // default constructor
   Person(const string &, const string &, char, const string &);  // alternate constructor
   // Default copy constructor does not need to be prototyped
   // Person(const Person &) = default;  // copy constructor
   Person &operator=(const Person &); // overloaded assignment operator
   virtual ~Person() = default;  // virtual destructor
   const string &GetFirstName() const { return firstName; }  // firstName returned as reference to const string  
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const string &GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
   void SetGreeting(const string &);
   virtual const string &Speak() { return greeting; }  // note return type of const string & (we're no longer returning a literal)
   virtual void Print() const; 
};

// Remember, using system-supplied default constructor, copy constructor and destructor

Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t), greeting("Hello")

{
}

// We're using the default, system-supplied copy constructor, but if you wrote it, it would look like:
/*
Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), 
                                  middleInitial(p.middleInitial), title(p.title), greeting(p.greeting)
{
}
*/

Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      // Note: there's no dynamically allocated data members, so implementing = is straightforward 
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = p.title;
      greeting = p.greeting;
   }
   return *this;  // allow for cascaded assignments
}

void Person::ModifyTitle(const string &newTitle)
{
   title = newTitle;
}

void Person::SetGreeting(const string &newGreeting)
{
   greeting = newGreeting;
}


void Person::Print() const
{
   cout << title << " " << firstName << " " << lastName << endl;
}


// Adapter Class -- uses private inheritance. Could have also used an association
// Decided this should be an abstract class, so Converse is a pure virtual function (albeit with an optional definition!)
// Derived classes will still need to override this pure virtual function if they'd like to be instantiable (concrete classes)
// Humanoid is primarily an Adapter class, however, is is secondarily a Target class, as derived class instances of this type 
// can be generalized as Humanoid *'s and manipulated in the Client (application).
class Humanoid: private Person
{
protected:
   void SetTitle(const string &t) { ModifyTitle(t); }  // calls Person::ModifyTitle()
public:
   Humanoid() = default;   
   Humanoid(const string &, const string &, const string &, const string &); 
   // Remember, it's unnecessary to prototype default copy constructor
   // Humanoid(const Humanoid &h) = default; // if we wrote copy constructor ourselves, we'd add : Person(h) { }  
   Humanoid &operator=(const Humanoid &h) { return dynamic_cast<Humanoid &>(Person::operator=(h)); }  
   // Since destructor has been indicated as virtual in base class, we don't need to protytpe it here if we're using default
   // ~Humanoid() override = default;   
   // Added interfaces for the Adapter class - due to private inheritance, inherited interfaces are hidden outside the scope of Humaniod
   const string &GetSecondaryName() const { return GetFirstName(); }  
   const string &GetPrimaryName() const { return GetLastName(); } 
   const string &GetTitle() const { return Person::GetTitle(); }   // Scope resolution needed on GetTitle() to avoid recursion
   void SetSalutation(const string &m) { SetGreeting(m); }
   virtual void GetInfo() { Print(); }
   virtual const string &Converse() = 0;  // Pure virtual function prototype
};

Humanoid::Humanoid(const string &n2, const string &n1, const string &planetNation, const string &greeting): 
                   Person(n2, n1, ' ', planetNation) 
{ 
   SetGreeting(greeting); 
} 

const string &Humanoid::Converse()   // Yes, there can be a default implementation for a pure virtual function
{                                    // but it can not be specified inline
   return Speak();
}


// One of several Target classes
class Orkan: public Humanoid
{
public:
   Orkan() = default;   // default constructor
   Orkan(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "Nanu nanu") { } 
   // Remember, it's unnecessary to prototype default copy constructor
   // Orkan(const Orkan &h) = default;  // If we instead wrote copy constructor ourselves, we'd add : Humanoid(h) { } 
   Orkan &operator=(const Orkan &h) { return dynamic_cast<Orkan &>(Humanoid::operator=(h)); }
   // Since destructor has been indicated as virtual in base class, we don't need to protytpe it here if we're using default
   // ~Orkan() override = default;  // virtual destructor
   const string &Converse() override;  // We must override this method if we want Orkan to be a concrete class
};

const string &Orkan::Converse()    
{                                  
   return Humanoid::Converse();   // even if we just call the default implementation, we must provide a method here
}


// One of several Target classes
class Romulan: public Humanoid
{
public:
   Romulan() = default;   // default constructor
   Romulan(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "jolan'tru") { } 
   // Remember, it's unnecessary to prototype default copy constructor
   // Romulan(const Romulan &h) = default;  // If we instead wrote copy constructor ourselves, we'd add : Humanoid(h) { } 
   Romulan &operator=(const Romulan &h) { return dynamic_cast<Romulan &>(Humanoid::operator=(h)); }
   // Since destructor has been indicated as virtual in base class, we don't need to protytpe it here if we're using default
   // ~Romulan() override = default; // virtual destructor
   const string &Converse() override;  // We must override this method if we want Romulan to be a concrete class
};

const string &Romulan::Converse()    
{                                  
   return Humanoid::Converse();   // even if we just call the default implementation, we must provide a method here
}


// One of several Target classes
class Earthling: public Humanoid
{
public:
   Earthling() = default;   // default constructor
   Earthling(const string &n2, const string &n1, const string &t) : Humanoid(n2, n1, t, "Hello") { } 
   // Remember, it's unnecessary to prototype default copy constructor
   // Earthling(const Earthling &h) = default;  // If we instead wrote copy constructor, we'd add : Humanoid(h) { }  
   Earthling &operator=(const Earthling &h) { return dynamic_cast<Earthling &>(Humanoid::operator=(h)); }
   // Since destructor has been indicated as virtual in base class, we don't need to protytpe it here if we're using default
   // ~Earthling() { }  // virtual destructor
   const string &Converse() override;  // We must override this method if we want Romulan to be a concrete class
};

const string &Earthling::Converse()    
{                                  
   return Humanoid::Converse();   // even if we just call the default implementation, we must provide a method here
}


int main()
{
   list<Humanoid *> allies;
   Orkan *o1 = new Orkan("Mork", "McConnell", "Orkan");
   Romulan *r1 = new Romulan("Donatra", "Jarok", "Romulan");
   Earthling *e1 = new Earthling("Eve", "Xu", "Earthling");

   // Add Humanoid *'s to the allies list. The list will make copies of the objects internally and will
   // properly clean up these objects when they are no longer members of the list.
   // You are responsible to delete and heap instances you provide to the list when you are done with them.

   // Add various derived types of Humanoid to the list 
   allies.push_back(o1);
   allies.push_back(r1);
   allies.push_back(e1);

   // Create a list iterator and set to first item in the list - notice type of iterator (base class type) versus auto. 
   // We're collecting by the base class type (generalizing)
   list <Humanoid *>::iterator listIter = allies.begin();
   while (listIter != allies.end())
   {
       (*listIter)->GetInfo();
       cout << (*listIter)->Converse() << endl;
       ++listIter;   // pre-increment preferred (efficiency)
   }

   // Though each type of Humanoid has a default Salutation, each may expand their language skills and choose an alternate language
   e1->SetSalutation("Bonjour");
   e1->GetInfo();   
   cout << e1->Converse() << endl;  // Show the Earthling's revised language capabilities

   delete o1;   // delete the heap instances
   delete r1;
   delete e1;

   return 0;
}
