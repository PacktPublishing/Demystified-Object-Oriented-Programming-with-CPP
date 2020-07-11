// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate static data members and static member functions.

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
    const char *studentId;  // pointer to constant string
    static int numStudents; // static data member
public:
    // member function prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, float, const char *, const char *); 
    Student(const Student &);  // copy constructor
    ~Student();  // destructor

    void Print() const;
    const char *GetFirstName() const { return firstName; }  
    const char *GetLastName() const { return lastName; } 
    char GetMiddleInitial() const { return middleInitial; }
    float GetGpa() const { return gpa; }
    const char *GetCurrentCourse() const 
        { return currentCourse; }
    const char *GetStudentId() const { return studentId; }
    void SetCurrentCourse(const char *);

    static int GetNumberStudents(); // static member function 
};

// definition for static data member 
// (which is implemented as external variable)
int Student::numStudents = 0;  // notice initial value of 0

// Definition for static member function
inline int Student::GetNumberStudents()
{
    return numStudents;
}

inline void Student::SetCurrentCourse(const char *c) 
{
    delete currentCourse;  
    currentCourse = new char [strlen(c) + 1];
    strcpy(currentCourse, c); 
}

Student::Student() : studentId (0) // default constructor
{
    firstName = lastName = 0;  // NULL pointer
    middleInitial = '\0';
    gpa = 0.0;
    currentCourse = 0;
    numStudents++;
}

// Alternate constructor member function definition
Student::Student(const char *fn, const char *ln, char mi, 
          float avg, const char *course, const char *id) 
{
    firstName = new char [strlen(fn) + 1];
    strcpy(firstName, fn);
    lastName = new char [strlen(ln) + 1];
    strcpy(lastName, ln);
    middleInitial = mi;
    gpa = avg;
    currentCourse = new char [strlen(course) + 1];
    strcpy(currentCourse, course);
    char *temp = new char [strlen(id) + 1];
    strcpy (temp, id);  // studentId can't be an lvaue,  
    studentId = temp;   // but temp can!
    numStudents++;
}

// Copy constructor definition
Student::Student(const Student &s) 
{
    firstName = new char [strlen(s.firstName) + 1];
    strcpy(firstName, s.firstName);
    lastName = new char [strlen(s.lastName) + 1];
    strcpy(lastName, s.lastName);
    middleInitial = s.middleInitial;
    gpa = s.gpa;
    currentCourse = new char [strlen(s.currentCourse) + 1];
    strcpy(currentCourse, s.currentCourse);
    char *temp = new char [strlen(s.studentId) + 1];
    strcpy (temp, s.studentId); //studentId can't be an lvaue, 
    studentId = temp;           // but temp can!
    numStudents++;
}
   
// destructor definition
Student::~Student()
{
    delete firstName;
    delete lastName;
    delete currentCourse;
    delete (char *) studentId; // cast is necessary for delete
    numStudents--;
}

void Student::Print() const
{
   cout << firstName << " " << middleInitial << ". ";
   cout << lastName << " with id: " << studentId;
   cout << " and gpa: " << gpa << " and is enrolled in: ";
   cout << currentCourse << endl;
}

int main()
{
   Student s1("Nick", "Cole", 'S', 3.65, "C++", "112HAV"); 
   Student s2("Alex", "Tost", 'A', 3.78, "C++", "674HOP"); 

   cout << s1.GetFirstName() << " " << s1.GetLastName();
   cout << " Enrolled in " << s1.GetCurrentCourse() << endl;
   cout << s2.GetFirstName() << " " << s2.GetLastName();
   cout << " Enrolled in " << s2.GetCurrentCourse() << endl;
   
   // call a static member function in the preferred manner
   cout << "There are " << Student::GetNumberStudents(); 
   cout << " students" << endl;

   // Though not preferable, we could also use:
   // cout << "There are " << s1.GetNumberStudents(); 
   // cout << " students" << endl;

   return 0;
}
