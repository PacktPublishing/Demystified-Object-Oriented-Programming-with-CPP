// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate virtual base classes.
// Virtual base classes resolve duplications which can exist with 
// multiple inheritance when two or more base classes for a class share 
// a common ancestor class.  
// In this example, only one copy of the LifeForm sub-object will exist for each
// instance of a Centaur.

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::string;

class LifeForm
{
private:
   int lifeExpectancy;
public:
   LifeForm() { lifeExpectancy = 0; }
   LifeForm(int life) { lifeExpectancy = life; }
   LifeForm(const LifeForm &form) { lifeExpectancy = form.lifeExpectancy; }
   virtual ~LifeForm() { }
   int GetLifeExpectancy() const { return lifeExpectancy; }

   // Virtual functions will not be inlined since their method must be determined
   // at run time using the v-table.
   virtual void Print() const = 0;   // pure virtual functions specify the interface but
   virtual string IsA() const = 0;   // most often do not specify a default behavior
   virtual string Speak() const = 0;
};

// Here, LifeForm is a virtual base class of Horse.  This means that if
// Horse is ever combined with a sibling (or cousin) of another base class which inherits
// from LifeForm, those siblings will SHARE their copy of LifeForm,
// reducing storage, extra constructor calls, and eliminating ambiguity. 
// This will not at all affect instances of Horse (only instances of
// derived classes which would otherwise have duplicate LifeForm sub-objects).

class Horse: public virtual LifeForm
{
private:
   string name;
public:
   Horse(): LifeForm(35), name("") { }
   Horse(const string &n);
   Horse(const Horse &);
   virtual ~Horse() { }
   const string &GetName() const { return name; }
   virtual void Print() const override;
   virtual string IsA() const override;
   virtual string Speak() const override;
};

// Notice that the base class initialization list is ignored
// if LifeForm actually is a shared virtual base class.
// Most often the default construcor will instead be called for LifeForm.
// The remainder of the member initialization list will be used as expected.
Horse::Horse(const string &n) : LifeForm(35), name("")
{
}

Horse::Horse(const Horse &h) : LifeForm (h), name(h.name)
{
}

void Horse::Print() const
{
   cout << name << endl;
}

string Horse::IsA() const
{
   return "Horse";
}

string Horse::Speak() const
{
   return "Neigh!";
}

// LifeForm is a virtual base class of Person.  
class Person: public virtual LifeForm
{
private:
   // data members
   string firstName;
   string lastName;
   char middleInitial;
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const string &);  // Make this operation available to derived classes
public:
   Person();   // default constructor
   Person(const string &, const string &, char, const string &);  // alternate constructor
   Person(const Person &);  // copy constructor
   virtual ~Person();  // destructor

   // inline function definitions
   const string &GetFirstName() const { return firstName; }  // firstName returned as ref to const string
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const string &GetTitle() const { return title; }
   char GetMiddleInitial() const { return middleInitial; }

   // Virtual functions will not be inlined since their method must be determined
   // at run time using the v-table.
   virtual void Print() const override;
   virtual string IsA() const override;
   virtual string Speak() const override;
};

// Notice that the base class initialization list is ignored
// if LifeForm actually is a shared virtual base class.
// Most often the default construcor will instead be called for LifeForm.
// The remainder of the member initialization list will be utilized, as expected.
Person::Person() : LifeForm(80), firstName(""), lastName(""), middleInitial('\0'), title("")
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : LifeForm(80),
                             firstName(fn), lastName(ln), middleInitial(mi), title(t)

{
}

Person::Person(const Person &p) : LifeForm(p), firstName(p.firstName), lastName(p.lastName),
                                               middleInitial(p.middleInitial), title(p.title)
{
}

Person::~Person()
{
}

void Person::ModifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::Print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". " << lastName << endl;
}

string Person::IsA() const
{  
    return "Person"; 
}

string Person::Speak() const
{  
    return "Hello!"; 
}

class Centaur: public Person, public Horse
{
private:
   // no additional data members required 
public:
   Centaur(): LifeForm(1000) { }
   Centaur(const string &, const string &, char = ' ', const string & = "Mythological Creature"); 
   Centaur(const Centaur &c): 
           Person(c), Horse(c),LifeForm(1000) { }
   virtual void Print() const override;
   virtual string IsA() const override;   
   virtual string Speak() const override;
};

// Constructors for Centaur need to specify how the shared
// base class LifeForm will be initialized. This is only allowed because LifeForm is a
// virtual base class of Person and Horse
Centaur::Centaur(const string &fn, const string &ln, char mi, const string &title): 
                 Person(fn, ln, mi, title), Horse(fn), 
                 LifeForm(1000)
{
   // All initialization has been taken care of in init. list
}

void Centaur::Print() const
{
   cout << "My name is " << GetFirstName();
   cout << ".  I am a " << GetTitle() << endl;
}

string Centaur::IsA() const
{ 
   return "Centaur"; 
}


string Centaur::Speak() const
{
   return "Neigh! and Hello! I'm a master of two languages.";
} 

int main()
{
   Centaur beast("Wild", "Man");
   cout << beast.Speak() << endl;
   cout << "I am a " << beast.IsA() << ". ";
   beast.Print();
   cout << "I will live: ";
   cout << beast.GetLifeExpectancy();  // no longer ambiguous!
   cout << " years" << endl; 
   return 0;
}

