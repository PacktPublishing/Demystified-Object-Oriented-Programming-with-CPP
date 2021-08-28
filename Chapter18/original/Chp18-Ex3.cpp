// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a simple Adapter class, which is a wrapper

#include <iostream>
#include <cstring>
using namespace std;

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
   Person &operator=(const Person &); // assignment operator
   virtual ~Person();  // destructor
   const char *GetFirstName() const { return firstName; }  // firstName returned as const string
   const char *GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return title; }
   char GetMiddleInitial() const { return middleInitial; }
   void SetGreeting(const char *);
   virtual const char *Speak() { return greeting; }
   virtual void Print();
};

Person objectRead;   // holds the object from the current read to support a simulation of a DB read

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
      // if 'this' had values for strings, delete the existing firstName, lastName, etc.
      if (firstName)
          delete firstName;  // or call ~Person(); (unusual)
      if (lastName)
          delete lastName;
      if (title)
          delete title;
      if (greeting)
          delete greeting;

      // if source object's strings are not null, let's copy them. If they are null, set 'this' counterparts to null
      if (p.firstName)
      {
          firstName = new char [strlen(p.firstName) + 1];
          strcpy(firstName, p.firstName);
      }
      else
          firstName = 0; 

      if (p.lastName)
      {
          lastName = new char [strlen(p.lastName) + 1];
          strcpy(lastName, p.lastName);
      }
      else
          lastName = 0;

      middleInitial = p.middleInitial;

      if (p.title)
      {
          title = new char [strlen(p.title) + 1];
          strcpy(title, p.title);
      }
      else
          title = 0;

      if (p.greeting)
      {
          greeting = new char [strlen(p.greeting) + 1];
          strcpy(greeting, p.greeting);
      }
      else
          greeting = 0;
   }
   return *this;  // allow for cascaded assignments
}

Person::~Person()
{
   delete firstName;
   delete lastName;
   delete title;
   delete greeting;
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


// External database access function

void db_open(const char *dbName)
{
    // Assume implementation exists
    cout << "Opening database: " << dbName << endl;
}

void db_close(const char *dbName)
{
    // Assume implementation exists
    cout << "Closing database: " << dbName << endl;
}

Person &db_read(const char *dbName, const char *key)
{
    // Assume implementation exists
    cout << "Reading from: " << dbName << " using key: " << key << endl; 
    // In a true implementation, we would read the data 
    // using the key and return the object we read in
    return objectRead;  
}

const char *db_write(const char *dbName, Person &data)
{
    // Assume implementation exists
    const char *key = data.GetLastName(); 
    cout << "Writing: " << key << " to: " << dbName << endl;  
    return key;
}


// CitizenDataBase is the Adapter class (the class wrapping the undesired interfaces) 
// We are wrapping the aforementioned external functions.
class CitizenDataBase
{
private: 
    char *name;
public:
    // No default constructor (unusual)
    CitizenDataBase(const char *);
    CitizenDataBase(const CitizenDataBase &) = delete ;  // prohibit copies 
    CitizenDataBase &operator=(const CitizenDataBase &) = delete;  // prohibit assignment 
    virtual ~CitizenDataBase();  // destructor
    Person &Read(const char *);
    const char *Write(Person &);
};


CitizenDataBase::CitizenDataBase(const char *n)
{
    name = new char [strlen(n) + 1];
    strcpy(name, n);
    db_open(name);   // calling an existing external function
}


CitizenDataBase::~CitizenDataBase()
{
    db_close(name);  // close database with external function
    delete name;
}

Person &CitizenDataBase::Read(const char *key)
{
    return db_read(name, key);   // call external function
}


const char *CitizenDataBase::Write(Person &data)
{
    return db_write(name, data);  // call external function
}

int main()
{
    const char *key;
    char name[] = "PersonData";

    Person p1("Curt", "Jeffreys", 'M', "Mr."); 
    Person p2("Frank", "Burns", 'W', "Mr.");
    Person p3;

    CitizenDataBase People(name);   // create a Database
    key = People.Write(p1);
    p3 = People.Read(key);

    return 0;
}
