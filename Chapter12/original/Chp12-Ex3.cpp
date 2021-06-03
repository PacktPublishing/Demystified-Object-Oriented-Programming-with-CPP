// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate operator overloading, both as member functions and
// non-member functions.  

#include <iostream>
#include <cstring>
using namespace std;


class Person
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

   virtual void Print() const;
   virtual void IsA();   

   // An overloaded assignment operator is not inherited by derived classes, therefore 
   // it must be defined by each class in the hierarchy.  Neglecting to provide an 
   // overloaded assignment operator will force the compiler to provide you with the 
   // default definition for assignment between to objects of the same type--a shallow or
   // C-like memcpy().  This is dangerous for any class which contains data members which
   // are pointers.
   Person &operator=(const Person &);  // overloaded assignment operator prototype
   bool operator==(const Person &);     // overloaded comparison operator prototype
   Person &operator+(const char *);    // overloaded + prototype
   friend Person &operator+(const char *, Person &);  // non-member friend function for operator+ 
};                                                    // so operands can be associative

Person::Person()
{
   firstName = lastName = 0;  // NULL pointer
   middleInitial = '\0';
   title = 0;
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
}

Person::~Person()
{
   delete firstName;
   delete lastName;
   delete title;
}

Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)  
   {
      delete firstName;  // or call ~Person();
      delete lastName;
      delete title; 

      firstName = new char [strlen(p.firstName) + 1];
      strcpy(firstName, p.firstName);
      lastName = new char [strlen(p.lastName) + 1];
      strcpy(lastName, p.lastName);
      middleInitial = p.middleInitial;
      title = new char [strlen(p.title) + 1];
      strcpy(title, p.title);
   }
   return *this;  // allow for cascaded assignments
}

bool Person::operator==(const Person &p)
{
   // if the objects are the same object, they are equal
   if (this == &p)
      return true;
   // if the contents of the objects are the same,
   // we'll say the objects are still equivalent
   else if ( (!strcmp(firstName, p.firstName)) &&
             (!strcmp(lastName, p.lastName)) &&
             (!strcmp(title, p.title)) &&
             (middleInitial == p.middleInitial) )
      return true;
   else
      return false;
}

Person &Person::operator+(const char *t)
{
   ModifyTitle(t);
   return *this;
}

// Since operator+ is not a member function of Person, it must
// be a friend of Person in order to have input parameter p access
// its protected member ModifyTitle()
Person &operator+(const char *t, Person &p)
{
   p.ModifyTitle(t);
   return p;
}

void Person::ModifyTitle(const char *newTitle)
{
   delete title;  // delete old title
   title = new char [strlen(newTitle) + 1];
   strcpy(title, newTitle);
}

void Person::Print() const
{
   if (title)
      cout << title << " ";
   if (firstName)
      cout << firstName << " ";
   else
      cout << "No first name ";  
   if (middleInitial != '\0')
      cout << middleInitial << ". ";
   if (lastName)
      cout << lastName << endl;
   else
      cout << "No last name" << endl;
}

void Person::IsA()
{
   cout << "Person" << endl;
}

int main()
{
   Person p1;
   Person p2("Gabby", "Doone", 'A', "Miss");
   Person p3("Renee", "Alexander", 'Z', "Dr.");
   
   p1.Print();
   p2.Print();
   p3.Print();

   p1 = p2;   // invoke overloaded assignment operator
   p1.Print();

   p2 = "Ms." + p2;  // invoke overloaded + operator
                     // then invoke overloaded = operator
   p2.Print();

   p1 = p2 = p3;  // overloaded assignment operator can handle this case too
   p2.Print();
   p1.Print();

   if (p2 == p2)    // invoke overloaded comparison operator
     cout << "Same people" << endl;

   if (p1 == p3)
     cout << "Same people" << endl;

   return 0;
}

