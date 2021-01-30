// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a simple Adapter class, using association between Adapter and Adaptee. 

#include <iostream>
#include <cstring>
#include <list>
using namespace std;

// Person is the Adaptee class (the class requiring an adaptation)
class Person
{
private: 
   char *firstName;
   char *lastName;
   char middleInitial;
   char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
   char *greeting;
protected:
public:
   Person();   // default constructor
   Person(const char *, const char *, char, const char *);  // alternate constructor
   Person(const Person &);  // copy constructor
   virtual ~Person();  // destructor
   const char *GetFirstName() const { return firstName; }  // firstName returned as const string  
   const char *GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
   void SetGreeting(const char *);
   void ModifyTitle(const char *);     // Moved to public for association example (was protected)
   virtual const char *Speak() { return greeting; } 
   virtual void Print(); 
};

Person::Person()
{
   firstName = lastName = 0;  // NULL pointer
   middleInitial = '\0';
   title = 0;
   greeting = 0;
}

Person::Person(const char *fn, const char *ln, char mi, const char *t)
{
   firstName = new char [strlen(fn) + 1];
   strcpy(firstName, fn);
   lastName = new char [strlen(ln) + 1];
   strcpy(lastName, ln);
   middleInitial = mi;
   title = new char [strlen(t) + 1];
   strcpy(title, t);
   greeting = new char [strlen("Hello") + 1];
   strcpy(greeting, "Hello");
}

Person::Person(const Person &pers)
{
   firstName = new char [strlen(pers.firstName) + 1];
   strcpy(firstName, pers.firstName);
   lastName = new char [strlen(pers.lastName) + 1];
   strcpy(lastName, pers.lastName);
   middleInitial = pers.middleInitial;
   title = new char [strlen(pers.title) + 1];
   strcpy(title, pers.title);
   greeting = new char [strlen(pers.greeting) + 1];
   strcpy(greeting, pers.greeting);
}

Person::~Person()
{
   delete firstName;
   delete lastName;
   delete title;
}

void Person::ModifyTitle(const char *newTitle)
{
   delete title;  // delete old title
   title = new char [strlen(newTitle) + 1];
   strcpy(title, newTitle);
}

void Person::SetGreeting(const char *newGreeting)
{
   delete greeting;  // delete old title
   greeting = new char [strlen(newGreeting) + 1];
   strcpy(greeting, newGreeting);
}


void Person::Print()
{
   cout << title << " " << firstName << " " << lastName << endl;
}


// Adapter Class -- an association to Adaptee.
// Humanoid is primarily an Adapter class, however, is is secondarily a Target class, as derived class instances of this type 
// can be generalized as Humanoid *'s and manipulated in the Client (application).
class Humanoid
{
private:
   Person *life;  // delegate all requests to the associated object
protected:
   void SetTitle(const char *t) { life->ModifyTitle(t); }
public:
   Humanoid() { life = 0; }
   Humanoid(const char *, const char *, const char *, const char *); 
   Humanoid(const Humanoid &h);  
   virtual ~Humanoid() { delete life; }  // destructor
   const char *GetSecondaryName() const { return life->GetFirstName(); }  
   const char *GetPrimaryName() const { return life->GetLastName(); }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return life->GetTitle(); } 
   void SetSalutation(const char *m) { life->SetGreeting(m); }
   virtual void GetInfo() { life->Print(); }
   virtual const char *Converse() = 0;  // Pure virtual function prototype
};

Humanoid::Humanoid(const char *n2, const char *n1, const char *planetNation, const char *greeting)
{ 
   // instantiate the associated object (Adaptee)
   life = new Person(n2, n1, ' ', planetNation);
   life->SetGreeting(greeting); 
} 

Humanoid::Humanoid(const Humanoid &h) 
{
   // instantiate the associated object (Adaptee)
   life = new Person(h.GetSecondaryName(), h.GetPrimaryName(), ' ', h.GetTitle());
   life->SetGreeting(h.life->Speak());  // Remember, life member is a Person *
}

const char *Humanoid::Converse()   // Yes, there can be a default implementation for a pure virtual function
{                                  // but it can not be specified inline
   return life->Speak();
}


// One of several Target classes
class Orkan: public Humanoid
{
public:
   Orkan();   // default constructor
   Orkan(const char *n2, const char *n1, const char *t) : Humanoid(n2, n1, t, "Nanu nanu") { } 
   Orkan(const Orkan &h) : Humanoid(h) { }  // copy constructor
   virtual ~Orkan() { }  // destructor
   virtual const char *Converse() override;  // We must override this method if we want Orkan to be a concrete class
};

const char *Orkan::Converse()    
{                                  
   return Humanoid::Converse();   // even if we just call the default implementation, we must provide a method here
}


// One of several Target classes
class Romulan: public Humanoid
{
public:
   Romulan();   // default constructor
   Romulan(const char *n2, const char *n1, const char *t) : Humanoid(n2, n1, t, "jolan'tru") { } 
   Romulan(const Romulan &h) : Humanoid(h) { }  // copy constructor
   virtual ~Romulan() { }  // destructor
   virtual const char *Converse() override;  // We must override this method if we want Romulan to be a concrete class
};

const char *Romulan::Converse()    
{                                  
   return Humanoid::Converse();   // even if we just call the default implementation, we must provide a method here
}


// One of several Target classes
class Earthling: public Humanoid
{
public:
   Earthling();   // default constructor
   Earthling(const char *n2, const char *n1, const char *t) : Humanoid(n2, n1, t, "Hello") { } 
   Earthling(const Romulan &h) : Humanoid(h) { }  // copy constructor
   virtual ~Earthling() { }  // destructor
   virtual const char *Converse() override;  // We must override this method if we want Romulan to be a concrete class
};

const char *Earthling::Converse()    
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

   // Create a list iterator and set to first item in the list
   list <Humanoid *>::iterator listIter = allies.begin();
   while (listIter != allies.end())
   {
       (*listIter)->GetInfo();
       cout << (*listIter)->Converse() << endl;
       listIter++;
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
