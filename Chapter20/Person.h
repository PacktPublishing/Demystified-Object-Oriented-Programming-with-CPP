// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Person class header file for pImpl pattern (with raw pointers)

#ifndef _PERSON_H
#define _PERSON_H

using std::string;

class Person
{
private: 
    class PersonImpl;  // forward declaration to nested class
    PersonImpl *pImpl; // pointer to implementation of class
protected:
    void ModifyTitle(const string &); 
public:
    Person();   // default constructor
    Person(const string &, const string &, char, const string &);  
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor
    // Notice, access functions are no longer inline (also hides implementation)
    const string &GetFirstName() const; 
    const string &GetLastName() const; 
    const string &GetTitle() const; 
    char GetMiddleInitial() const; 
    virtual void Print() const;
    virtual void IsA() const;  
    virtual void Greeting(const string &) const;
    Person &operator=(const Person &);  // overloaded assignment operator prototype
};

#endif
