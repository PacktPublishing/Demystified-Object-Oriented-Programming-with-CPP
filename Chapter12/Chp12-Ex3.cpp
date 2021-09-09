// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose:  To illustrate operator overloading, both as member functions and
// non-member functions.  
// Note: To fully demonstrate overloading operator= (with a deep assignment), we need one data member that is a pointer
// With that in mind, title will be a char * (rather than our preferred string) so that we can demonstrate this idea.

#include <iostream>
#include <cstring> // only here to help demonstrate a deep assignment (by including a pointer data member)

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Person
{
private: 
   string firstName;
   string lastName;
   char middleInitial = '\0';  // in-class initialization -- value to be used in default constructor
   char *title = nullptr;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const string &);  // Make this operation available to derived classes
public:
   Person() = default;   // default constructor
   Person(const string &, const string &, char, const char *);  // alternate constructor
   Person(const Person &);  // copy constructor
   virtual ~Person();  // destructor

   // inline function definitions
   const string &GetFirstName() const { return firstName; }  // firstName returned as const string  
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }

   virtual void Print() const;
   virtual void IsA() const;   

   // An overloaded assignment operator is not inherited by derived classes, therefore 
   // it must be defined by each class in the hierarchy.  Neglecting to provide an 
   // overloaded assignment operator will force the compiler to provide you with the 
   // default definition for assignment between to objects of the same type--a shallow or
   // C-like memcpy().  This is dangerous for any class which contains data members which
   // are pointers.
   Person &operator=(const Person &);  // overloaded assignment operator prototype
   bool operator==(const Person &);     // overloaded comparison operator prototype
   Person &operator+(const string &);    // overloaded + prototype
   friend Person &operator+(const string &, Person &);  // non-member friend function for operator+ 
};                                                    // so operands can be associative

// With in-class initialization, writing the default constructor yourself is no longer necessary
// Here's how it would look if you did choose to provide one (and also chose not to use in-class initialization)
/*
Person::Person() : middleInitial('\0'), title(nullptr)
{
   // Remember, string members are automatically initialized to empty with the default string constructor
   // dynamically allocate memory for any pointer data members here
}
*/

Person::Person(const string &fn, const string &ln, char mi, const char *t) :
               firstName(fn), lastName(ln), middleInitial(mi)
{
   title = new char[strlen(t) + 1];
   strcpy(title, t);
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
                                  middleInitial(p.middleInitial)
{
   title = new char[strlen(p.title) + 1];
   strcpy(title, p.title);
}


Person::~Person()
{
   delete title;
}

Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)  
   {
      // delete any previously dynamically allocated data members here from the destination object
      // or call ~Person() to release this memory -- unconventional
      delete title;

      // Also, remember to reallocate memory for any data members that are pointers.
      // copy from source to destination object each data member
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = new char[strlen(p.title) + 1];  // memory allocatinon for ptr member
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
   else if ( (!firstName.compare(p.firstName)) &&
             (!lastName.compare(p.lastName)) &&
             (!strcmp(title, p.title)) &&
             (middleInitial == p.middleInitial) )
      return true;
   else
      return false;
}

Person &Person::operator+(const string &t)
{
   ModifyTitle(t);
   return *this;
}

// Since operator+ is not a member function of Person, it must
// be a friend of Person in order to have input parameter p access
// its protected member ModifyTitle()
Person &operator+(const string &t, Person &p)
{
   p.ModifyTitle(t);
   return p;
}

void Person::ModifyTitle(const string &newTitle)
{
   delete title; // delete existing title - stored as a char * just for this example
   title = new char[strlen(newTitle.c_str()) + 1];   // get the c string equivalent from the string
   strcpy(title, newTitle.c_str());
}

void Person::Print() const
{
   if (title)
      cout << title << " ";
   if (!firstName.empty())
      cout << firstName << " ";
   else
      cout << "No first name ";  
   if (middleInitial != '\0')
      cout << middleInitial << ". ";
   if (!lastName.empty())
      cout << lastName << endl;
   else
      cout << "No last name" << endl;
}

void Person::IsA() const
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

