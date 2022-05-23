// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Person class header file 

#ifndef _PERSON_H
#define _PERSON_H

using std::string;

class Person
{
private:
   string firstName;
   string lastName;
   char middleInitial = '\0';  // in-class initialization -- value to be used in default constructor
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
   string greeting;
public:
   Person() = default;   // default constructor
   Person(const string &, const string &, char, const string &);  // alternate constructor
   // Remember, it is not necessary to prototype the default copy constructor
   // Person(const Person &) = default;  // copy constructor
   Person &operator=(const Person &); // overloaded assignment operator
   virtual ~Person();  // virtual destructor
   const string &GetFirstName() const { return firstName; }  // firstName returned as reference to const string
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const string &GetTitle() const { return title; }
   char GetMiddleInitial() const { return middleInitial; }
   void ModifyTitle(const string &);  
   void SetGreeting(const string &);
   virtual const string &Speak() { return greeting; }  // note return type of const string & (we're no longer returning a literal)
   virtual void Print() const;
};

#endif
