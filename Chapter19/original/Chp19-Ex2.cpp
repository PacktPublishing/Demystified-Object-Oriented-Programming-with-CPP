// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a Singleton class. 
// Implemented as a cooperating pair -- Singleton and SingletonDestroyer -- to make the Singleton
// This ensures proper destruction because the static non-pointer member SingletonDestroyer contains a link
// to the Singleton and, through association, forces its destruction. This happens when the static
// SingletonDestroyer is released. Otherwise, we'd be counting on someone to remember to delete Singleton
// which presents an issue -- many may point to the Singleton. Also, as the Singleton creates itself when 
// needed, the Singleton can (thourgh its pairing w SingletonDestroy) be in charge of its own destruction
// Nonetheless, we will add checks for single destruction in the rare case a Client deletes our Singleton directly.

#include <iostream>
#include <cstring>
#include <list>
using namespace std;

class Singleton;
class SingletonDestroyer;
class Person;
class President;

class SingletonDestroyer
{
private:
    Singleton *theSingleton;
public:
    SingletonDestroyer(Singleton *s = 0) { theSingleton = s; }
    SingletonDestroyer(const SingletonDestroyer &) = delete; // disallow copies
    SingletonDestroyer &operator=(const SingletonDestroyer &) = delete; // disallow assignment
    ~SingletonDestroyer();  // class is not meant to be customized, so destructor is not virtual
    void setSingleton(Singleton *s) { theSingleton = s; }  
    Singleton *getSingleton() { return theSingleton; }
};

// Singleton is designed to be mixed-in to a class desiring a Singleton using inheritance
// Note: static Singleton *instance(); method won't be included in this class for inheritance-model implementation of Singleton.
//       Target class will implement this method. If this was a stand-alone Singleton class, you'd include prototye here instead.
class Singleton
{
protected:
    static Singleton *theInstance;
    static SingletonDestroyer destroyer;
protected:
    Singleton() {}
    Singleton(const Singleton &) = delete; // disallow copies
    Singleton &operator=(const Singleton &) = delete; // disallow assignment
    friend class SingletonDestroyer;
    virtual ~Singleton() { cout << "Singleton destructor" << endl; }  // virtual because we'll inherit from Singleton
};

// External (name mangled) variables to hold static data members
Singleton *Singleton::theInstance = NULL;
SingletonDestroyer Singleton::destroyer;


SingletonDestroyer::~SingletonDestroyer()
{   // If Singleton has been directly deleted (rare), its destructor will have Nulled out SingletonDestructor's theSingleton member
    if (theSingleton == NULL)  
        cout << "SingletonDestroyer destructor: Singleton has already been destructed" << endl;
    else
    {
        cout << "SingletonDestroyer destructor" << endl;
        delete theSingleton;   // no need to Null out SingletonDestroyer's pointer to theSingleton after delete theSingleton; 
    }                          // This will have been done by Singleton if it has been individually destructed
}


// This method is not needed with inheritance-model implementation of Singleton. 
// Shown to demonstrate what you'd need if you had a stand-alone class
/* 
Singleton *Singleton::instance()
{
    if (theInstance == NULL)
    {
        theInstance = new Singleton();
        destroyer.setSingleton(theInstance);
        cout << "Creating the Singleton" << endl;
    }
    else
        cout << "Singleton previously created. Returning existing singleton" << endl;
    return theInstance;
}
*/

class Person
{
private:
   char *firstName;
   char *lastName;
   char middleInitial;
   char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
   char *greeting;
protected:
   void ModifyTitle(const char *);  // Make this operation available to derived classes
public:
   Person();   // default constructor
   Person(const char *, const char *, char, const char *);  // alternate constructor
   Person(const Person &);  // copy constructor
   Person &operator=(const Person &); // overloaded assignment operator
   virtual ~Person();  // destructor
   const char *GetFirstName() const { return firstName; }  // firstName returned as const string
   const char *GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return title; }
   char GetMiddleInitial() const { return middleInitial; }
   void SetGreeting(const char *);
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

Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      delete firstName;  // or call ~Person();
      delete lastName;
      delete title;
      delete greeting;

      firstName = new char [strlen(p.firstName) + 1];
      strcpy(firstName, p.firstName);
      lastName = new char [strlen(p.lastName) + 1];
      strcpy(lastName, p.lastName);
      middleInitial = p.middleInitial;
      title = new char [strlen(p.title) + 1];
      strcpy(title, p.title);
      greeting = new char [strlen(p.greeting) + 1];
      strcpy(greeting, p.greeting);
   }
   return *this;  // allow for cascaded assignments
}

Person::~Person()
{
   cout << "Person destructor" << endl;
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
   cout << title << " " << firstName << " " << middleInitial << " " << lastName << endl;
}


// A President Is-A Person yet mixes-in a Singleton (definitely!)
class President: public Person, public Singleton
{
private:
    President(const char *, const char *, char, const char *);
    // No default constructor - rare
public:
    virtual ~President(); // { destroyer.setSingleton(NULL); cout << "President destructor" << endl; }
    President(const President &) = delete;  // disallow copies
    President &operator=(const President &) = delete;
    static President *instance(const char *, const char *, char, const char *);
};

President::President(const char *fn, const char *ln, char mi, const char *t) : Person(fn, ln, mi, t), Singleton()
{
}

President::~President()
{
    destroyer.setSingleton(NULL);  // Necessary for the rare case that a Singleton is explicitly deleted. The SingletonDestructor
    cout << "President destructor" << endl;   // destructor will check this member to see if it's NULL before deallocating Singleton
}

President *President::instance(const char *fn, const char *ln, char mi, const char *t) 
{
    if (theInstance == NULL)    // If we have not yet allocated the Singleton
    {
        theInstance = new President(fn, ln, mi, t);    // Create one using private constructor
        destroyer.setSingleton(theInstance);           // Set our SingletonDestroyer to point to the Singleton
        cout << "Creating the Singleton" << endl;
    }
    else                                               // If an instance exists, return existing instance
        cout << "Singleton previously created. Returning existing singleton" << endl;
    return (President *) theInstance;   // cast necessary because President has been stored as a Singleton in theInstance
}


int main()
{
    President *p1 = President::instance("John", "Adams", 'Q', "President");
    President *p2 = President::instance("William", "Harrison", 'H', "President");
    // Verification there's only one object
    if (p1 == p2)
        cout << "Same instance (only one Singleton)" << endl;

    p1->Print();
 
    // Singleton is so long-lived that it is appropriate for it to be deleted at end of the application. 
    // Many users will have links to Singleton. Ideally, none of them should delete it. The SingletonDestructor will do so.
    // Just as Singleton allocates itself internally, so will it destruct on its own (with help from its paired Destructor)
    // However, this code is written such that if someone does delete p1; then the SingletonDestructor will recognize this    
    // and not doubly delete the Singleton which it is responsible for.

    return 0;
}

