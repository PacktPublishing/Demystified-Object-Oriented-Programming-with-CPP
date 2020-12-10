// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate single inheritance, how the member initilazation list
// is used to specify which base class constructor should be implicitly invoked,
// and the significance of the protected access region. 

// Here, we've generalized the attributes and behaviors relevant to a Person
// out of Student into the following class definition.    

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class Person
{
private: 
   // data members
   char *firstName;
   char *lastName;
   char middleInitial;
   char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const char *);  // Make this operation available to derived classes
public:
   Person();   // default constructor
   Person(const char *, const char *, char, const char *);  // alternate constructor
   Person(const Person &);  // copy constructor
   ~Person();  // destructor

   // inline function definitions
   const char *GetFirstName() const { return firstName; }  // firstName returned as const string  
   const char *GetLastName() const { return lastName; }    // so is lastName (via implicit cast)
   const char *GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
};

Person::Person()
{
   firstName = lastName = 0;  // NULL pointer
   middleInitial = '\0';
   title = 0;
}

Person::Person(const char *fn, const char *ln, char mi, const char *t)
{
   firstName = new char [strlen(fn) + 1];
   strcpy(firstName, fn);
   lastName = new char [strlen(ln) + 1];
   strcpy(lastName, ln);
   middleInitial = mi;
   title = new char [strlen(t) + 1];
   strcpy(title, t);
}

Person::Person(const Person &pers)
{
   firstName = new char [strlen(pers.firstName) + 1];
   strcpy(firstName, pers.firstName);
   lastName = new char [strlen(pers.lastName) + 1];
   strcpy(lastName, pers.lastName);
   middleInitial = pers.middleInitial;
   title = new char [strlen(pers.title) + 1];
   strcpy(title, pers.title);
}

Person::~Person()
{
   delete firstName;
   delete lastName;
   delete title;
}

void Person::ModifyTitle(const char *newTitle)
{
   delete title;  // delete old title
   title = new char [strlen(newTitle) + 1];
   strcpy(title, newTitle);
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
   char *currentCourse;
   const char *studentId;  // pointer to constant string, not constant pointer
public:
   // member function prototypes
   Student();  // default constructor
   Student(const char *, const char *, char, const char *, float, const char *, const char *); // alt. constructor
   Student(const Student &);  // copy constructor
   ~Student();  // destructor
   void Print() const;

   void EarnPhD();  // public interface to inherited protected member

   // inline function definitions
   float GetGpa()  const { return gpa; }
   const char *GetCurrentCourse() const { return currentCourse; }
   const char *GetStudentId() const { return studentId; }

   // prototype only, see inline function definiton below
   void SetCurrentCourse(const char *);
};

inline void Student::SetCurrentCourse(const char *c)
{
   delete currentCourse;   // delete existing course
   currentCourse = new char [strlen(c) + 1];
   strcpy(currentCourse, c); 
}

Student::Student() : studentId (0) 
{
   gpa = 0.0;
   currentCourse = 0;
}

// Alternate constructor member function definition
// Notice that the member initialization list is used to select
// which constructor should be utilized to initialize the Person
// sub-object as well as to pass arguments up to this constructor
Student::Student(const char *fn, const char *ln, char mi, const char *t,
       float avg, const char *course, const char *id) : Person(fn, ln, mi, t)
{
   gpa = avg;
   currentCourse = new char [strlen(course) + 1];
   strcpy(currentCourse, course);
   char *temp = new char [strlen(id) + 1];
   strcpy (temp, id); // studentId can't be an lvaue, but temp can!
   studentId = temp;
}

// Copy constructor definition
// Notice that the member initialization list is used to specify 
// that the Person copy constructor should be utilized to copy the 
// Person sub-object.  Without this secification, the default constructor
// for Person would be invoked (which would be incorrect since part of
// the copied Student object would be Nulled out).  Notice that
// the input parameter ps is implicitly cast to a Person &
Student::Student(const Student &ps) : Person(ps)
{
   gpa = ps.gpa;
   currentCourse = new char [strlen(ps.currentCourse) + 1];
   strcpy(currentCourse, ps.currentCourse);
   char *temp = new char [strlen(ps.studentId) + 1];
   strcpy (temp, ps.studentId); // studentId can't be an lvaue, but temp can!
   studentId = temp;
}
   
// destructor definition
Student::~Student()
{
   delete currentCourse;
   delete (char *) studentId;
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
