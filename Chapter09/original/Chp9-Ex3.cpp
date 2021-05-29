// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate virtual base classes.
// Virtual base classes resolve duplications which can exist with 
// multiple inheritance when two or more base classes for a class share 
// a common ancestor class.  
// In this example, only one copy of the LifeForm sub-object will exist for each
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
    LifeForm(const LifeForm &form) 
       { lifeExpectancy = form.lifeExpectancy; }
    virtual ~LifeForm() { }
    int GetLifeExpectancy() const { return lifeExpectancy; }
    virtual void Print() const = 0; 
    virtual const char *IsA() = 0;   
    virtual const char *Speak() = 0;
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
    char *name;
public:
    Horse() : LifeForm(35) { name = 0; }
    Horse(const char *n);
    Horse(const Horse &); 
    virtual ~Horse() { delete name; }
    const char *GetName() const { return name; }
    virtual void Print() const override { cout << name << endl; }
    virtual const char *IsA() override { return "Horse"; }
    virtual const char *Speak() override { return "Neigh!"; }
};

// Notice that the base class initialization list is ignored
// if LifeForm actually is a shared virtual base class.
// Most often the default construcor will instead be called for LifeForm.
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

// LifeForm is a virtual base class of Person.  
class Person: public virtual LifeForm
{
private: 
    // data members
    char *firstName;
    char *lastName;
    char middleInitial;
    char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
    void ModifyTitle(const char *);  
public:
    Person();   // default constructor
    Person(const char *, const char *, char, const char *);  
    Person(const Person &);  // copy constructor
    virtual ~Person();  // destructor
    const char *GetFirstName() const { return firstName; }  
    const char *GetLastName() const { return lastName; }    
    const char *GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }
    virtual void Print() const override;
    virtual const char *IsA() override;   
    virtual const char *Speak() override;
};

// Notice that the base class initialization list is ignored
// if LifeForm actually is a shared virtual base class.
// Most often the default construcor will instead be called for LifeForm.
Person::Person() : LifeForm(80)
{
    firstName = lastName = 0;  // NULL pointer
    middleInitial = '\0';
    title = 0;
}

Person::Person(const char *fn, const char *ln, char mi, const char *t) :
               LifeForm(80)
{
    firstName = new char [strlen(fn) + 1];
    strcpy(firstName, fn);
    lastName = new char [strlen(ln) + 1];
    strcpy(lastName, ln);
    middleInitial = mi;
    title = new char [strlen(t) + 1];
    strcpy(title, t);
}

// See comment on above constructor
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
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". " << lastName << endl;
}

const char *Person::IsA() 
{  
    return "Person"; 
}

const char *Person::Speak() 
{  
    return "Hello!"; 
}

class Centaur: public Person, public Horse
{
private:
   // no additional data members required 
public:
   Centaur(): LifeForm(1000) { }
   Centaur(const char *, const char *, char = ' ', const char * = "Mythological Creature"); 
   Centaur(const Centaur &c): 
           Person(c), Horse(c),LifeForm(1000) { }
   virtual void Print() const override;
   virtual const char *IsA() override;   
   virtual const char *Speak() override;
};

// Constructors for Centaur need to specify how the shared
// base class LifeForm will be initialized. This is only allowed because LifeForm is a
// virtual base class of Person and Horse
Centaur::Centaur(const char *fn, const char *ln, char mi, const char *title): 
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

const char *Centaur::IsA() 
{ 
   return "Centaur"; 
}


const char *Centaur::Speak() 
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

