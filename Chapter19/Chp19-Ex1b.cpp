// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a very simple Singleton implementation using a referenceable object. Note that the referenceable
// object representing the Singleton will be a static local variable in instance(). It will not be a static data member of the
// class (as that would be initialized before main() and as such, impossible to customize its construction.
// The fallback here is that we always have the singleton, we can never get rid of it to replace it with another singleton.
// This may be ok, but may not be. Consider a Singleton President. We have one. That one goes away, then we have a new one.     
// Only one at a time in that scenario, but we'd like the flexibility to change which one it is (for that scenario, a pointer works better). 

#include <iostream>
using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Singleton
{
private:
    string data;
    Singleton(string d); // private to prevent multiple instantiation
public:
    static Singleton &instance(string);
    // destructor is called for the static local variable in instance() before the application ends 
    virtual ~Singleton();   // virtual so you can extend the Singleton with a Target class
    const string &getData() const { return data; }
};

Singleton::Singleton(string d) : data(d)
{ 
    cout << "Constructor" << endl; 
}  

Singleton::~Singleton()
{
    cout << "Destructor" << endl; 
}

// If you extend the Singleton with a Target class, you will want to move instance() to the Target class.
// The Target class will change the signature to match the signature in its private constructors (to pass the arguments along)
Singleton &Singleton::instance(string d)
{
    static Singleton theInstance(d);   // create the Singleton with desired constructor. Note: we can never replace the Singleton in this approach! 
                                       // Remember, static local variables are only created and initialized exactly once, guaranteeing one Singleton!
    return theInstance;
}

int main()
{
    Singleton &s1 = Singleton::instance("Unique data"); // first call, creates theInstance 
    Singleton &s2 = Singleton::instance("More data"); // returns existing theInstance

    cout << s1.getData() << "\n" << s2.getData() << endl;
    return 0; 
} 
