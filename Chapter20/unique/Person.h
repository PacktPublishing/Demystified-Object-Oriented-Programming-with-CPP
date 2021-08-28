// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Person class header file using a unique pointer to model association between Person and PersonImpl

#ifndef _PERSON_H
#define _PERSON_H
#include <memory>

using std::string;

class Person
{
private: 
    class PersonImpl;  // forward declaration to nested class
    std::unique_ptr<PersonImpl> pImpl; // pointer to implementation of class
protected:
    void ModifyTitle(const string &); 
public:
    Person();   // default constructor
    Person(const string &, const string &, char, const string &);  
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor
    const string &GetFirstName() const; // { return firstName; }  
    const string &GetLastName() const; // { return lastName; }    
    const string &GetTitle() const; // { return title; } 
    char GetMiddleInitial() const; // { return middleInitial; }
    virtual void Print() const;
    virtual void IsA() const;  
    virtual void Greeting(const string &) const;
    Person &operator=(const Person &);  // overloaded assignment operator prototype
};

#endif
