// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Person class header file using a unique pointer to model association between Person and PersonImpl

#ifndef _PERSON_H
#define _PERSON_H
#include <memory>

class Person
{
private: 
    class PersonImpl;  // forward declaration to nested class
    std::unique_ptr<PersonImpl> pImpl; // pointer to implementation of class
protected:
    void ModifyTitle(const char *); 
public:
    Person();   // default constructor
    Person(const char *, const char *, char, const char *);  
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor
    const char *GetFirstName() const; // { return firstName; }  
    const char *GetLastName() const; // { return lastName; }    
    const char *GetTitle() const; // { return title; } 
    char GetMiddleInitial() const; // { return middleInitial; }
    virtual void Print() const;
    virtual void IsA();  
    virtual void Greeting(const char *);
    Person &operator=(const Person &);  // overloaded assignment operator prototype
};

#endif
