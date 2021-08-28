// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a simple Adapter class, which is a wrapper

#include <iostream>

using std::cout;    // preferable to: using namespace std;
using std::endl;
using std::string;

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

Person objectRead;   // holds the object from the current read to support a simulation of a DB read

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


// External database access function

void db_open(const string &dbName)
{
    // Assume implementation exists
    cout << "Opening database: " << dbName << endl;
}

void db_close(const string &dbName)
{
    // Assume implementation exists
    cout << "Closing database: " << dbName << endl;
}

Person &db_read(const string &dbName, const string &key)
{
    // Assume implementation exists
    cout << "Reading from: " << dbName << " using key: " << key << endl; 
    // In a true implementation, we would read the data 
    // using the key and return the object we read in
    return objectRead;  
}

const string &db_write(const string &dbName, Person &data)
{
    // Assume implementation exists
    const string &key = data.GetLastName(); 
    cout << "Writing: " << key << " to: " << dbName << endl;  
    return key;
}


// CitizenDataBase is the Adapter class (the class wrapping the undesired interfaces) 
// We are wrapping the aforementioned external functions.
class CitizenDataBase
{
private: 
    string name;
public:
    // No default constructor (unusual)
    CitizenDataBase(const string &);
    CitizenDataBase(const CitizenDataBase &) = delete ;  // prohibit copies 
    CitizenDataBase &operator=(const CitizenDataBase &) = delete;  // prohibit assignment 
    virtual ~CitizenDataBase();  // destructor
    Person &Read(const string &);
    const string &Write(Person &);
};


CitizenDataBase::CitizenDataBase(const string &n) : name(n)
{
    db_open(name);   // calling an existing external function
}


CitizenDataBase::~CitizenDataBase()
{
    db_close(name);  // close database with external function
}

Person &CitizenDataBase::Read(const string &key)
{
    return db_read(name, key);   // call external function
}


const string &CitizenDataBase::Write(Person &data)
{
    return db_write(name, data);  // call external function
}

int main()
{
    string key;
    string name("PersonData");

    Person p1("Curt", "Jeffreys", 'M', "Mr."); 
    Person p2("Frank", "Burns", 'W', "Mr.");
    Person p3;

    CitizenDataBase People(name);   // create a Database
    key = People.Write(p1);
    p3 = People.Read(key);

    return 0;
}
