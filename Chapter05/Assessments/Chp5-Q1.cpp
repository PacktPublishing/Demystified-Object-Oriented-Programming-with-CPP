// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Sample Solution to Chp 5, Exercise 1, parts a - e. 

#include <iostream>  

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Student
{
private: 
    // data members
    string firstName;           // note: string data members will be default constructed (they are member objects of type string)
    string lastName;
    char middleInitial = '\0';  // in-class initialization
    float gpa = 0.0;            // in-class initialization
    string currentCourse;  
    const int studentId = 0;   // constant data member 
public:
    // member function prototypes
    Student() = default;  // let's use system provided default constructor - we still want this signature for instantiation, so we include it here
    Student(const string &, const string &, char, float, const string &, int); 
    Student(const Student &);  // copy constructor
    ~Student();  // destructor
    void Print();
    const string &GetFirstName() { return firstName; }  
    const string &GetLastName() { return lastName; }    
    char GetMiddleInitial() { return middleInitial; }
    float GetGpa() { return gpa; }
    const string &GetCurrentCourse() { return currentCourse; }
    void SetCurrentCourse(const string &);  // prototype only
};

inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;   // the implementation using the string is far simplier
}


// default constructor - note this is commented out because the system supplied detault constructor is adequate -
// everything is set either by in-class initialization, above, or is a member object and default constructed (string members)
/*
Student::Student() 
{
    // You may still set data members here, but using in-class initialization or the member initialization is more efficient than using assignment
    // Note: firstName, lastName, currentCourse (string member objects) are each default constructed with the string constructor 
}
*/

// Alternate constructor
// note: member init. list is used to set data members 
Student::Student(const string &fn, const string &ln, char mi, float avg, const string &course, int id) : 
                 firstName(fn), lastName(ln), middleInitial(mi), gpa(avg), currentCourse(course), studentId (id)
{
   // note: for string data members, the above initialization is calling the constructor matching the signature of item in ()'s
   // this is inevitably more efficient than default constructing the data member and then assigning it with a new value in the method body
   // note: any pointer data members often need to be set within body of function (but can sometimes be set in init. list too)
}

// Copy constructor - note: the default copy constructor would be adequate here if we don't need the print statement with cout
// member init. list used to set studentId
Student::Student(const Student &s) : firstName(s.firstName), lastName(s.lastName), middleInitial(s.middleInitial), 
                                     gpa(s.gpa), currentCourse(s.currentCourse), studentId (s.studentId)
{
   cout << "Copy constructor" << endl;
   // remember to do a deep copy for any data members that are pointers
}


// Destructor - note, the default destructor would be adequate if we do not desire the print statement using cout
Student::~Student()
{
   cout << "Destructor" << endl;
   // remember to delete memory for any data members that are pointers
}

void Student::Print()
{
    cout << firstName << " " << middleInitial << ". ";
    cout << lastName << " with id: " << studentId;
    cout << " and gpa: " << gpa << " is enrolled in: ";
    cout << currentCourse << endl;

}

int main()
{
    Student s0;  // default constructed Student
    
    Student s1("Renee", "Alexander", 'Z', 3.7, "C++", 1290);   // alternate constructed Student
    cout << s1.GetFirstName() << " " << s1.GetLastName();
    cout <<  " has gpa of: " << s1.GetGpa() << endl;

    Student *s2 = new Student("Delilah", "Alexander", 'C', 3.5, "C++", 1111);   // alternate constructed Student, dynamically allocated
    cout << s2->GetFirstName() << " " << s2->GetLastName();
    cout <<  " has gpa of: " << s1.GetGpa() << endl;

    Student s3(s1);  // copy constructor - same as: Student s3 = s1;  (provided this is on one line, that is, initialization)
    cout << s3.GetFirstName() << " " << s3.GetLastName();
    cout <<  " has gpa of: " << s3.GetGpa() << endl;

    delete s2;   // deallocate memory for s2 (will also trigger destruction)
    return 0;
}
