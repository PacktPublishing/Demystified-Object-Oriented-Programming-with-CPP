// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To understand const data members and 
// the member initialization list

#include <iostream>  
#include <cstring> 
using namespace std;

class Student
{
private: 
    // data members
    char *firstName;
    char *lastName;
    char middleInitial;
    float gpa;
    char *currentCourse;
    const int studentId;   // constant data member
public:
    // member function prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, float, const char *, int); 
    Student(const Student &);  // copy constructor
    ~Student();  // destructor
    void Print();
    const char *GetFirstName() { return firstName; }  
    const char *GetLastName() { return lastName; }    
    char GetMiddleInitial() { return middleInitial; }
    float GetGpa() { return gpa; }
    const char *GetCurrentCourse() { return currentCourse; }
    void SetCurrentCourse(const char *);  // prototype only
};

inline void Student::SetCurrentCourse(const char *c)
{
    delete currentCourse;  
    currentCourse = new char [strlen(c) + 1];
    strcpy(currentCourse, c); 
}


// Member init. list is used to set studentId and gpa
Student::Student() : studentId(0), gpa(0.0)  
{
   firstName = lastName = 0;  // NULL pointer
   middleInitial = '\0';
   currentCourse = 0;
}

// member init. list is used to set studentId, gpa, and middleInitial
Student::Student(const char *fn, const char *ln, char mi, float avg, 
         const char *course, int id) : studentId (id), gpa (avg),
                                 middleInitial(mi)
{
   firstName = new char [strlen(fn) + 1];
   strcpy(firstName, fn);
   lastName = new char [strlen(ln) + 1];
   strcpy(lastName, ln);
   currentCourse = new char [strlen(course) + 1];
   strcpy(currentCourse, course);
}

// member init. list used to set studentId
Student::Student(const Student &s) : studentId (s.studentId)
{
   firstName = new char [strlen(s.firstName) + 1];
   strcpy(firstName, s.firstName);
   lastName = new char [strlen(s.lastName) + 1];
   strcpy(lastName, s.lastName);
   middleInitial = s.middleInitial;
   gpa = s.gpa;
   currentCourse = new char [strlen(s.currentCourse) + 1];
   strcpy(currentCourse, s.currentCourse);
}

Student::~Student()
{
    delete firstName;
    delete lastName;
    delete currentCourse;
}

void Student::Print()
{
    cout << firstName << " " << middleInitial << ". ";
    cout << lastName << " has a gpa of: " << gpa;
    cout << " and is enrolled in: " << currentCourse << endl;
}

int main()
{
    Student s1("Renee", "Alexander", 'Z', 3.7, "C++", 1290);
    cout << s1.GetFirstName() << " " << s1.GetLastName();
    cout <<  " has gpa of: " << s1.GetGpa() << endl;

    return 0;
}
