// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate how duplications can exist with multiple inheritance  
// when two or more base classes of a class share a common ancestor class.
// In this example, two copies of a LifeForm sub-object will exist for each
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

class Horse: public LifeForm
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


class Person : public LifeForm
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
   cout << GetTitle() << " " << GetFirstName() << " ";
   cout << GetMiddleInitial() << ". " << GetLastName() << endl;
}

string Person::IsA() const
{
   return "Person";
}

string Person::Speak() const
{
   return "Hello!";
}


class Centaur : public Person, public Horse
{
private:
   // no additional data members required 
public:
   Centaur() { }
   Centaur(const string &, const string &, char = ' ', const string & = "Mythological Creature"); 
   Centaur(const Centaur &c): Person(c), Horse(c) { }
   virtual void Print() const override;
   virtual string IsA() const override;   
   virtual string Speak() const override;
};

Centaur::Centaur(const string &fn, const string &ln, char mi, const string &title) : 
                 Person(fn, ln, mi, title), Horse(fn)
{    
   // All initialization has been taken care of in init. list 
}

void Centaur::Print() const
{
   // GetFirstName is defined in Person.  So is GetTitle()
   cout << "My name is " << GetFirstName();
   cout << ".  I am a " << GetTitle() << endl;
}

string Centaur::IsA() const
{
   return "Centaur";
}

string Centaur::Speak() const
{
   return "Neigh! and Hello!";
}

int main()
{
   Centaur beast("Wild", "Man");
   cout << beast.Speak() << " I'm a " << beast.IsA() << endl;

   // Ambiguous member function invocation below!  Two paths exist to 
   // LifeForm::GetLifeExpectancy().  One via Horse and one via Person.
   // Also, two copies of the LifeForm object exist--one initialized the
   // way Horse dictated, one initialized the way Person dictated.  Which
   // of these two LifeForms are you asking to be the 'this' pointer? 
   // cout << beast.GetLifeExpectancy();  
 
   cout << "It is unclear how many years I will live: ";
   cout << beast.Person::GetLifeExpectancy(); 
   cout << " or ";
   cout << beast.Horse::GetLifeExpectancy() << endl; 

   return 0;
}

