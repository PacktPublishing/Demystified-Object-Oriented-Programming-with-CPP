// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate single inheritance, how the member initilazation list
// is used to specify which base class constructor should be implicitly invoked,
// and the significance of the protected access region. 

// Here, we've generalized the attributes and behaviors relevant to a Person
// out of Student into the following class definition.    

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setprecision;
using std::string;

class Person
{
private: 
   // data members
   string firstName;
   string lastName;
   char middleInitial;
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const string &);  // Make this operation available to derived classes
public:
   Person();   // default constructor
   Person(const string &, const string &, char, const string &);  // alternate constructor
   Person(const Person &);  // copy constructor
   ~Person();  // destructor

   // inline function definitions
   const string &GetFirstName() const { return firstName; }  // firstName returned as const string  
   const string &GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const string &GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
};

Person::Person() : firstName(""), lastName(""), middleInitial('\0'), title("")
{
   // dynamically allocate memory for any pointer data members here
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : 
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
   // dynamically allocate memory for any pointer data members here
}

Person::Person(const Person &p) :
               firstName(p.firstName), lastName(p.lastName), 
               middleInitial(p.middleInitial), title(p.title)
{
   // deep copy any pointer data members here
}

Person::~Person()
{
   // release memory for any dynamically allocated data members
}

void Person::ModifyTitle(const string &newTitle)
{
   title = newTitle;     // assignment between strings ensures a deep assignment
}

// Student is derived from Person using public inheritance.
// (Notice the public access label after the : in the class definition).
// Private inheritance is the default for classes (public is the default
// for inherited structures).

class Student : public Person
{
private: 
   // data members
   float gpa;
   string currentCourse;
   const string studentId;  // studentId is not modifiable 
public:
   // member function prototypes
   Student();  // default constructor
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
};

inline void Student::SetCurrentCourse(const string &c)
{
   currentCourse = c; 
}

Student::Student() : gpa(0.0), currentCourse(""), studentId ("")    
{
   // note: since studentId is const, if the Student is default constructed, this id will always be empty.
   // Another approach, would be to generate a unique id always and use this in both constructors
   // dynamically allocate memory for any pointer data members here
}

// Alternate constructor member function definition
// Notice that the member initialization list is used to select
// which constructor should be utilized to initialize the Person
// sub-object as well as to pass arguments up to this constructor
Student::Student(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id) : Person(fn, ln, mi, t),
                       gpa(avg), currentCourse(course), studentId(id)
{
   // dynamically allocate memory for any pointer data members here
}

// Copy constructor definition
// Notice that the member initialization list is used to specify 
// that the Person copy constructor should be utilized to copy the 
// Person sub-object.  Without this secification, the default constructor
// for Person would be invoked (which would be incorrect since part of
// the copied Student object would be Nulled out).  Notice that
// the input parameter ps is implicitly cast to a Person &
Student::Student(const Student &s) : Person(s),
                 gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
   // deep copy any pointer data members of derived class here
   
}
   
// destructor definition
Student::~Student()
{
   // release memory for any dynamically allocated data members
   
}

void Student::Print() const
{
   // Private members of Person are not directly accessible within
   // the scope of Student, hence access functions are utilized
   // to print these members
   cout << GetTitle() << " " << GetFirstName() << " ";
   cout << GetMiddleInitial() << ". " << GetLastName();
   cout << " with id: " << studentId << " gpa: ";
   cout << setprecision(2) << gpa;
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

   return 0;
}
