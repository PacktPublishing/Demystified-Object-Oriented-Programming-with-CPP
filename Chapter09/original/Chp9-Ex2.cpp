// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate how duplications can exist with multiple inheritance  
// when two or more base classes of a class share a common ancestor class.
// In this example, two copies of a LifeForm sub-object will exist for each
// instance of a Centaur.

#include <iostream>
#include <cstring>
using namespace std;


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
   virtual void Print() const = 0; // pure virtual functions specify the interface but
   virtual const char *IsA() = 0;   // most often do not specify a default behavior
   virtual const char *Speak() = 0;
};

class Horse: public LifeForm
{
private:
   char *name;
public:
   Horse(): LifeForm(35) { name = 0; }
   Horse(const char *n);
   Horse(const Horse &); 
   virtual ~Horse() { delete name; }
   const char *GetName() const { return name; }
   virtual void Print() const override;
   virtual const char *IsA() override;
   virtual const char *Speak() override;
};

Horse::Horse(const char *n) : LifeForm(35)
{
   name = new char [strlen(n) + 1];
   strcpy(name, n);
}

Horse::Horse(const Horse &h) : LifeForm (h)
{
   name = new char [strlen(h.name) + 1];
   strcpy(name, h.name); 
}

void Horse::Print() const
{
   cout << name << endl;
}

const char *Horse::IsA()
{
   return "Horse"; 
}

const char *Horse::Speak()
{
   return "Neigh!"; 
}


class Person : public LifeForm
{
private: 
   // data members
   char *firstName;
   char *lastName;
   char middleInitial;
   char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const char *);  // Make this operation available to derived classes
public:
   Person();   // default constructor
   Person(const char *, const char *, char, const char *);  // alternate constructor
   Person(const Person &);  // copy constructor
   virtual ~Person();  // destructor

   // inline function definitions
   const char *GetFirstName() const { return firstName; }  // firstName returned as const string  
   const char *GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }

   // Virtual functions will not be inlined since their method must be determined
   // at run time using the v-table.
   virtual void Print() const override;
   virtual const char *IsA() override;   
   virtual const char *Speak() override;
};

Person::Person() : LifeForm(80)
{
   firstName = lastName = 0;  // NULL pointer
   middleInitial = '\0';
   title = 0;
}

Person::Person(const char *fn, const char *ln, char mi, const char *t) : LifeForm(80)
{
   firstName = new char [strlen(fn) + 1];
   strcpy(firstName, fn);
   lastName = new char [strlen(ln) + 1];
   strcpy(lastName, ln);
   middleInitial = mi;
   title = new char [strlen(t) + 1];
   strcpy(title, t);
}

Person::Person(const Person &pers) : LifeForm(pers)
{
   firstName = new char [strlen(pers.firstName) + 1];
   strcpy(firstName, pers.firstName);
   lastName = new char [strlen(pers.lastName) + 1];
   strcpy(lastName, pers.lastName);
   middleInitial = pers.middleInitial;
   title = new char [strlen(pers.title) + 1];
   strcpy(title, pers.title);
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

void Person::Print() const
{
   cout << GetTitle() << " " << GetFirstName() << " ";
   cout << GetMiddleInitial() << ". " << GetLastName() << endl;
}

const char *Person::IsA()
{
   return "Person";
}

const char *Person::Speak()
{
   return "Hello!";
}


class Centaur : public Person, public Horse
{
private:
   // no additional data members required 
public:
   Centaur() { }
   Centaur(const char *, const char *, char = ' ', const char * = "Mythological Creature"); 
   Centaur(const Centaur &c): Person(c), Horse(c) { }
   virtual void Print() const override;
   virtual const char *IsA() override;   
   virtual const char *Speak() override;
};

Centaur::Centaur(const char *fn, const char *ln, char mi, const char *title) : 
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

const char *Centaur::IsA()
{
   return "Centaur";
}

const char *Centaur::Speak() 
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

