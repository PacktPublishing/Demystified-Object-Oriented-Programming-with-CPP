// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate single inheritance, how the member initilazation list
// is used to specify which base class constructor should be implicitly invoked,
// and the significance of the protected access region. 

// Here, we've generalized the attributes and behaviors relevant to a Person
// out of Student into the following class definition.    

#include <iostream>
#include <iomanip>

using std::cout;     // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

class Person
{
private: 
   // data members
   string firstName;       // strings, as member objects, will have their default constructor called, init. to an empty string.
   string lastName;        // so that they do not require in-class initialization
   char middleInitial = '\0';  // in-class initialization -- value to be used in default constructor
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const string &);  // Make this operation available to derived classes
public:
   Person() = default;   // default constructor 
   Person(const string &, const string &, char, const string &);  // alternate constructor
   Person(const Person &) = default;  // use default copy constructor
   ~Person() = default;  // default destructor; note: = default prototype is optional (we'd get default dest w/o any prototype)

   // inline function definitions
   const string &GetFirstName() const { return firstName; }  // firstName returned as const string  
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const string &GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
};

// With in-class initialization, writing the default constructor yourself is no longer necessary 
// Here's how it would look if you did choose to provide one (and also chose not to use in-class initialization)
/* 
Person::Person() : middleInitial('\0')
{
   // Remember, string members are automatically initialized to empty with the default string constructor
   // dynamically allocate memory for any pointer data members here
}
*/

Person::Person(const string &fn, const string &ln, char mi, const string &t) : 
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
   // dynamically allocate memory for any pointer data members here
}

// We are using default copy constructor, but if you needed to write it yourself, here is what it would look like:
/*
Person::Person(const Person &p) :
               firstName(p.firstName), lastName(p.lastName), 
               middleInitial(p.middleInitial), title(p.title)
{
   // deep copy any pointer data members here
}
*/

// We don't need to write the destructor ourselves since we have no heap memory to release, but this is what it would look like
/* 
Person::~Person()
{
   // release memory for any dynamically allocated data members
}
*/

void Person::ModifyTitle(const string &newTitle)
{
   title = newTitle;     // assignment between strings ensures a deep assignment
}

// Student is derived from Person using public inheritance. (Notice the public access label after the : in the class definition).
// Private inheritance is the default for classes (public is the default for inherited structures).

class Student : public Person
{
private: 
   // data members
   float gpa = 0.0;         // in-class initialization 
   string currentCourse;
   const string studentId;  // studentId is not modifiable 
   static int numStudents;  // static data member is initialized outside of class (see below)
public:
   // member function prototypes
   Student();   // default constructor
   Student(const string &, const string &, char, const string &, float, const string &, const string &); // alt. constructor
   Student(const Student &);  // copy constructor
   ~Student();  // destructor
   void Print() const;

   void EarnPhD();  // public interface to inherited protected member

   // inline function definitions
   float GetGpa()  const { return gpa; }
   const string &GetCurrentCourse() const { return currentCourse; }
   const string &GetStudentId() const { return studentId; }

   // prototype only, see inline function definiton below
   void SetCurrentCourse(const string &);

   static int GetNumberStudents(); // static member function
};

// definition for static data member (which is implemented as external variable)
int Student::numStudents = 0;  // notice initial value of 0


inline void Student::SetCurrentCourse(const string &c)
{
   currentCourse = c; 
}

// Definition for static member function (it is also inline)
inline int Student::GetNumberStudents()
{
    return numStudents;
}

// Notice that data members using in-class initialization (above), will be set for those members not in the member init list. 
// However, those that can not be easily set with in-class initialization (such as static numStudents), we set below in method. 
// Recall that member objects (strings) will be default constructed, so no additional init is necessary (if an empty string is our goal)
Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
   // Note: since studentId is const, we need to set it at construction. We're doing so in member init list with 
   // a unique id (based upon numStudents counter + 100), concatenated with the string "Id" .
   // Remember, string member currentCourse will be default constructed with an empty string - it is a member object
   // Remember to dynamically allocate memory for any pointer data members here (not needed in this example)
   numStudents++;
}

// Alternate constructor member function definition
// Notice that the member initialization list is used to select which constructor should be utilized to initialize the Person
// sub-object as well as to pass arguments up to this constructor
Student::Student(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id) : Person(fn, ln, mi, t),
                       gpa(avg), currentCourse(course), studentId(id)
{
   // Remember to dynamically allocate memory for any pointer data members here (not needed in this example)
   numStudents++;
}

// Copy constructor definition
// Notice that the member initialization list is used to specify 
// that the Person copy constructor should be utilized to copy the 
// Person sub-object.  Without this secification, the default constructor
// for Person would be invoked (which would be incorrect since part of
// the copied Student object would be Nulled out).  Notice that
// the input parameter s is implicitly cast to a Person &
Student::Student(const Student &s) : Person(s),
                 gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
   // deep copy any pointer data members of derived class here
   numStudents++;
}
   
// destructor definition
Student::~Student()
{
   // release memory for any dynamically allocated data members
   numStudents--;
}

void Student::Print() const
{
   // Private members of Person are not directly accessible within
   // the scope of Student, hence access functions are utilized
   // to print these members
   cout << GetTitle() << " " << GetFirstName() << " ";
   cout << GetMiddleInitial() << ". " << GetLastName();
   cout << " with id: " << studentId << " gpa: ";
   cout << setprecision(3) << gpa;
   cout << " course: " << currentCourse << endl;
}

void Student::EarnPhD()
{
   // Protected members defined by the base class are accessible within
   // the scope of the derived class.  EarnPhd() provides a public
   // interface to this functionality for derived class instances. 
   ModifyTitle("Dr.");  
}

int main()
{
   Student s1("Jo", "Li", 'U', "Ms.", 3.9, "C++", "178PSU"); 

   // Public members of Person and Student are accessable outside the scope
   // of their respective classes....

   s1.Print();

   s1.SetCurrentCourse("Doctoral Thesis");
   s1.EarnPhD();

   s1.Print();
   cout << "Total number of students: " << Student::GetNumberStudents() << endl;

   return 0;
}
