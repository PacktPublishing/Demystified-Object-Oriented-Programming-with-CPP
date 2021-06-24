// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To understand const data members and the member initialization list
// Note: The constructor member initialization list was originally created to provide a manner to initialize data members
// that are const or references. However, it can additionally (and preferably) be used as an efficient way to fully initialize
// virtually any data member.

#include <iostream>  

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

class Student
{
private: 
    // data members
    string firstName;
    string lastName;
    char middleInitial;
    float gpa;
    string currentCourse;  // let's finally convert this to a std::string -- we've illustrated most ptr special needs within classes by now 
    const int studentId;   // constant data member
public:
    // member function prototypes
    Student();  // default constructor
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


// Member init. list is used to set data members 
Student::Student() : firstName(), lastName(), middleInitial('\0'), gpa(0.0), currentCourse(), studentId(0)  
{
    // You may still set data members here, but using above initialization is more efficient than using assignment
    // Note: firstName, lastName, currentCourse are shown in member init. list selecting default constructor for initialization.
    // However, as this is the default action for member objects (string), we don’t need to explicitly include
    // these members in the member initialization list (nor will we include them in future examples).

}

// member init. list is used to set data members 
Student::Student(const string &fn, const string &ln, char mi, float avg, const string &course, int id) : 
                 firstName(fn), lastName(ln), middleInitial(mi), gpa(avg), currentCourse(course), studentId (id)
{
   // note: for string data members, the above initialization is calling the constructor matching the signature of item in ()'s
   // this is inevitably more efficient than default constructing the data member and then assigning it with a new value in the method body
   // note: any pointer data members often need to be set within body of function (but can sometimes be set in init. list too)
}

// member init. list used to set studentId
Student::Student(const Student &s) : firstName(s.firstName), lastName(s.lastName), middleInitial(s.middleInitial), 
                                     gpa(s.gpa), currentCourse(s.currentCourse), studentId (s.studentId)
{
   // remember to do a deep copy for any data members that are pointers
}

Student::~Student()
{
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
    Student s1("Renee", "Alexander", 'Z', 3.7, "C++", 1290);
    cout << s1.GetFirstName() << " " << s1.GetLastName();
    cout <<  " has gpa of: " << s1.GetGpa() << endl;

    return 0;
}
