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
    char middleInitial = '\0';   // in-class initialization
    char *title = nullptr;       // we'll keep this data member as a char * to demonstrate deep copy/assignment
protected:
    void ModifyTitle(const string &);
public:
    Person() = default;   // default constructor
    Person(const string &, const string &, char, const char *);
    Person(const Person &);  // copy constructor
    Person(Person &&);  // move copy constructor
    virtual ~Person();  // virtual destructor

    // inline function definitions
    const string &GetFirstName() const { return firstName; }
    const string &GetLastName() const { return lastName; }
    const char *GetTitle() const { return title; }
    char GetMiddleInitial() const { return middleInitial; }

    const string &SetLastName(const string &);

    // Virtual functions will (usually) not be inlined since their method must be determined at run time using v-table (except rare cases)
    virtual void Print() const;
    virtual void IsA() const;
    virtual void Greeting(const string &) const;

    Person &operator=(const Person &);  // overloaded assignment operator prototype
    Person &operator=(Person &&);  // move overloaded assignment operator prototype

};

#endif
