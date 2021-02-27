// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Person class header file for pImpl pattern (with raw pointers)

#ifndef _PERSON_H
#define _PERSON_H

class Person
{
private: 
    class PersonImpl;  // forward declaration to nested class
    PersonImpl *pImpl; // pointer to implementation of class
protected:
    void ModifyTitle(const char *); 
public:
    Person();   // default constructor
    Person(const char *, const char *, char, const char *);  
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor
    // Notice, access functions are no longer inline (also hides implementation)
    const char *GetFirstName() const; 
    const char *GetLastName() const; 
    const char *GetTitle() const; 
    char GetMiddleInitial() const; 
    virtual void Print() const;
    virtual void IsA();  
    virtual void Greeting(const char *);
    Person &operator=(const Person &);  // overloaded assignment operator prototype
};

#endif
