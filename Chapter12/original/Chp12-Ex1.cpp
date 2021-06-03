// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate friend classes and friend functions 
// This program shows simple syntax and example access allowed in the body of Id::SetStudent(Student *);

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

class Student; // forward declaration

class Id
{
private:
   char *idNumber;
   Student *student;
   const char *GetId() const { return idNumber; }  // provide private access method for a friend scope usage
public:
   Id() { idNumber = 0; }
   Id(const char *); 
   Id(const Id &);  
   ~Id() { delete idNumber; }
   void SetStudent(Student *s);  
   friend class Student;    // all member functions in Student are friends of Id
};

Id::Id(const char *id)
{
   idNumber = new char [strlen(id) + 1];
   strcpy(idNumber, id);
}

Id::Id(const Id &id)
{
   idNumber = new char [strlen(id.idNumber) + 1];
   strcpy(idNumber, id.idNumber);
}

class Person
{
private: 
    // data members
    char *firstName;
    char *lastName;
    char middleInitial;
    char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
    void ModifyTitle(const char *); 
public:
    Person();   // default constructor
    Person(const char *, const char *, char, const char *);  
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor

    // inline function definitions
    const char *GetFirstName() const { return firstName; }  
    const char *GetLastName() const { return lastName; }    
    const char *GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }

    // Virtual functions 
    virtual void Print() const;
    virtual void IsA();  
    virtual void Greeting(const char *);
};

Person::Person()
{
    firstName = lastName = 0;  // NULL pointer
    middleInitial = '\0';
    title = 0;
}

Person::Person(const char *fn, const char *ln, char mi, 
               const char *t)
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

void Person::Print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". " << lastName << endl;
}

void Person::IsA()
{
    cout << "Person" << endl;
}

void Person::Greeting(const char *msg)
{
    cout << msg << endl;
}

class Student : public Person  // whole
{
private: 
    // data members
    float gpa;
    char *currentCourse;
    static int numStudents;
    Id *studentId;  
public:
    // member function prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, const char *,
            float, const char *, const char *); 
    Student(const Student &);  // copy constructor
    virtual ~Student();  // destructor
    void EarnPhD();  
    float GetGpa() const { return gpa; }  // various inline fns.
    const char *GetCurrentCourse() const { return currentCourse; }
    void SetCurrentCourse(const char *); // prototype only
    virtual void Print() const override;
    virtual void IsA() override;
    static int GetNumberStudents() { return numStudents; }
    // Access function for associated Id object
    const char *GetStudentId() const; // prototype only 
    // Only the following member function of Id is a friend function 
    friend void Id::SetStudent(Student *);  
};

int Student::numStudents = 0;  // definition of static data member


inline void Student::SetCurrentCourse(const char *c)
{
    delete currentCourse;   // delete existing course
    currentCourse = new char [strlen(c) + 1];
    strcpy(currentCourse, c); 
}

Student::Student() : studentId (new Id("None")) 
{
    gpa = 0.0;
    currentCourse = 0;
    studentId->SetStudent(this);  // create back link
    numStudents++;
}

Student::Student(const char *fn, const char *ln, char mi, 
                 const char *t, float avg, const char *course,
                 const char *id) : Person(fn, ln, mi, t), studentId(new Id(id))
{
    gpa = avg;
    currentCourse = new char [strlen(course) + 1];
    strcpy(currentCourse, course);
    studentId->SetStudent(this);  // create back link
    numStudents++;
}

Student::Student(const Student &ps) : Person(ps), studentId(new Id(ps.GetStudentId()))
{
    gpa = ps.gpa;
    currentCourse = new char [strlen(ps.currentCourse) + 1];
    strcpy(currentCourse, ps.currentCourse);
    studentId->SetStudent(this);  // create back link
    numStudents++;
}
   
// destructor definition
Student::~Student()
{
    delete currentCourse;
    numStudents--;
    delete studentId; // we allocated it, so we destroy it
}

void Student::EarnPhD()
{
    ModifyTitle("Dr.");  
}

void Student::Print() const
{   
    cout << GetTitle() << " " << GetFirstName() << " ";
    cout << GetMiddleInitial() << ". " << GetLastName();
    cout << " with id: " << studentId->GetId() << " GPA: ";    // note GetId() is private, but we're in 
    cout << setprecision(3) <<  " " << gpa;                    // the scope of a friend class
    cout << " Course: " << currentCourse << endl;
}

void Student::IsA()
{
    cout << "Student" << endl;
}

const char *Student::GetStudentId() const 
{ 
    // return studentId->idNumber;  // it's more polite to use the private access method than grab the member directly
    return studentId->GetId();  // note GetId() is private, but we're in the scope of a friend class
}

void Id::SetStudent(Student *s)
{
    student = s;
    // access below just to demonstrate friends -- that is, the student can access its private gpa here
    cout << "Set back link for " << student->GetFirstName() << " with gpa: " << student->gpa << endl;  
}

int main()
{
    Student s1("Cyrus", "Bond", 'I', "Mr.", 3.65, "C++", "6996CU"); 
    Student s2("Anne", "Brennan", 'M', "Ms.", 3.95, "C++", "909EU"); 

    cout << s1.GetFirstName() << " " << s1.GetLastName() << " has id #: "; 
    cout << s1.GetStudentId() << endl;

    cout << s2.GetFirstName() << " " << s2.GetLastName() << " has id #: "; 
    cout << s2.GetStudentId() << endl;

    return 0;
}

