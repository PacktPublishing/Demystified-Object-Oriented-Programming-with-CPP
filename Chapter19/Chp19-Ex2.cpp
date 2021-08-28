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
#include <list>
using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Singleton;
class SingletonDestroyer;
class Person;
class President;

class SingletonDestroyer
{
private:
    Singleton *theSingleton;
public:
    SingletonDestroyer(Singleton *s = nullptr) { theSingleton = s; }
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
Singleton *Singleton::theInstance = nullptr;
SingletonDestroyer Singleton::destroyer;


SingletonDestroyer::~SingletonDestroyer()
{   // If Singleton has been directly deleted (rare), its destructor will have Nulled out SingletonDestructor's theSingleton member
    if (theSingleton == nullptr)  
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
    if (theInstance == nullptr)
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
   string firstName;
   string lastName;
   char middleInitial;
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
   string greeting;
protected:
   void ModifyTitle(const string &);  // Make this operation available to derived classes
public:
   Person();   // default constructor
   Person(const string &, const string &, char, const string &);  // alternate constructor
   Person(const Person &);  // copy constructor
   Person &operator=(const Person &); // overloaded assignment operator
   virtual ~Person();  // destructor
   const string &GetFirstName() const { return firstName; }  // firstName returned as reference to const string
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const string &GetTitle() const { return title; }
   char GetMiddleInitial() const { return middleInitial; }
   void SetGreeting(const string &);
   virtual const string &Speak() { return greeting; }  // note return type of const string & (we're no longer returning a literal)
   virtual void Print() const;
};

Person::Person() : firstName(""), lastName(""), middleInitial('\0'), title(""), greeting("")
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t), greeting("Hello")

{
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
                                  middleInitial(p.middleInitial), title(p.title), greeting(p.greeting)
{
}

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

Person::~Person()
{
   cout << "Person destructor" << endl;
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

// A President Is-A Person yet mixes-in a Singleton (definitely!)
class President: public Person, public Singleton
{
private:
    President(const string &, const string &, char, const string &);
    // No default constructor - rare
public:
    virtual ~President(); // { destroyer.setSingleton(NULL); cout << "President destructor" << endl; }
    President(const President &) = delete;  // disallow copies
    President &operator=(const President &) = delete;
    static President *instance(const string &, const string &, char, const string &);
};

President::President(const string &fn, const string &ln, char mi, const string &t) : Person(fn, ln, mi, t), Singleton()
{
}

President::~President()
{
    destroyer.setSingleton(nullptr);  // Necessary for the rare case that a Singleton is explicitly deleted. The SingletonDestructor
    cout << "President destructor" << endl;   // destructor will check this member to see if it's NULL before deallocating Singleton
}

President *President::instance(const string &fn, const string &ln, char mi, const string &t) 
{
    if (theInstance == nullptr)    // If we have not yet allocated the Singleton
    {
        theInstance = new President(fn, ln, mi, t);    // Create one using private constructor
        destroyer.setSingleton(theInstance);           // Set our SingletonDestroyer to point to the Singleton
        cout << "Creating the Singleton" << endl;
    }
    else                                               // If an instance exists, return existing instance
        cout << "Singleton previously created. Returning existing singleton" << endl;
    return dynamic_cast<President *>(theInstance);   // cast necessary because President has been stored as a Singleton in theInstance
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

