// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a very simple Singleton implementation. In this implementation, destruction of the Singleton
// is not guaranteed. In fact, it won't happen unless the rare (unadvised) case of explicit deletion of the Singleton occurs. 

#include <iostream>
using namespace std;

class Singleton
{
private:
    static Singleton *theInstance;
    Singleton(); // private to prevent multiple instantiation
public:
    static Singleton *instance();
    // destructor is not called, unless you do so explicitly by deleting outer object, which is unlikely and atypical
    virtual ~Singleton();   // virtual so you can extend the Singleton with a Target class
};

// get the memory for the static data member
Singleton *Singleton::theInstance = NULL;

Singleton::Singleton() 
{ 
    cout << "Constructor" << endl; 
    theInstance = NULL;
}  

Singleton::~Singleton()
{ 
    cout << "Destructor" << endl; // note: this message will appear twice if you delete the Singleton. 
    if (theInstance != NULL)      // Second call (print) is on delete temp; before this check of theInstance != NULL to stop the recursion
    {
       Singleton *temp = theInstance;
       theInstance = NULL;   // removes pointer to actual Singleton 
       temp->theInstance = NULL;  // prevents recursion
       delete temp;   // makes for a recursive destructor call if you'd just call 'delete theInstance;'
    }                 // which is why we need to use a temp pointer and first null out 'theInstance' to stop the recursion 
}

// If you extend the Singleton with a Target class, you will want to move instance() to the Target class.
// The Target class will change the signature to match the signature in its private constructors (to pass the arguments along)
Singleton *Singleton::instance()
{
    if (theInstance == NULL)
        theInstance = new Singleton();  // allocate Singleton -- will be constructed (once)
    return theInstance;
}

int main()
{
    Singleton *s1 = Singleton::instance(); // first call, creates theInstance 
    Singleton *s2 = Singleton::instance(); // returns existing theInstance

    cout << s1 << " " << s2 << endl;
    
    // delete s1;   // delete s1 will ensure the destructor is called, 
}                   // but this is not typical that a Singleton will be deleted explicitly, 
                    // so depending on this is a poor design choice
