// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate friend classes and friend functions 
// This program shows simple syntax and example access allowed in the body of Id::SetStudent(Student *);

#include <iostream>
#include <iomanip>

using std::cout;   // preferred to using namespace std;
using std::endl;
using std::setprecision;
using std::string;

class Student; // forward declaration

class Id
{
private:
   string idNumber;
   Student *student;
   const string &GetId() const { return idNumber; }  // provide private access method for a friend scope usage
public:
   Id() : idNumber(""), student(nullptr) { }
   Id(const string &); 
   Id(const Id &);  
   ~Id() { }
   void SetStudent(Student *s);  
   friend class Student;    // all member functions in Student are friends of Id
};

Id::Id(const string &id) : idNumber(id), student(nullptr)
{
}

Id::Id(const Id &id) : idNumber(id.idNumber), student(id.student)
{
}

class Person
{
private:
    // data members
    string firstName;
    string lastName;
    char middleInitial;
    string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
    void ModifyTitle(const string &);
public:
    Person();   // default constructor
    Person(const string &, const string &, char, const string &);
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor

    // inline function definitions
    const string &GetFirstName() const { return firstName; }
    const string &GetLastName() const { return lastName; }
    const string &GetTitle() const { return title; }
    char GetMiddleInitial() const { return middleInitial; }

    // Virtual functions
    virtual void Print() const;
    virtual void IsA() const;
    virtual void Greeting(const string &) const;
};

Person::Person() : firstName(""), lastName(""), middleInitial('\0'), title("")
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
                                  middleInitial(p.middleInitial), title(p.title)
{
}

Person::~Person()
{
}

void Person::ModifyTitle(const string &newTitle)
{
    title = newTitle;
}

void Person::Print() const
{
    cout << title << " " << firstName << " ";
    cout << middleInitial << ". " << lastName << endl;
}

void Person::IsA() const
{
    cout << "Person" << endl;
}

void Person::Greeting(const string &msg) const
{
    cout << msg << endl;
}

class Student : public Person  // whole
{
private: 
    // data members
    float gpa;
    string currentCourse;
    static int numStudents;
    Id *studentId;  
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);  // copy constructor
    virtual ~Student();  // destructor
    void EarnPhD();  
    float GetGpa() const { return gpa; }  // various inline fns.
    const string &GetCurrentCourse() const { return currentCourse; }
    void SetCurrentCourse(const string &); // prototype only
    virtual void Print() const override;
    virtual void IsA() const override;
    static int GetNumberStudents() { return numStudents; }
    // Access function for associated Id object
    const string &GetStudentId() const; // prototype only 
    // Only the following member function of Id is a friend function 
    friend void Id::SetStudent(Student *);  
};

int Student::numStudents = 0;  // definition of static data member

inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student() : gpa(0.0), currentCourse(""), studentId(new Id("None"))
{
    studentId->SetStudent(this);  // create back link - note forward link in member init list
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course,
                 const string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(new Id(id))
{
    studentId->SetStudent(this);  // create back link - note forward link in member init list
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(new Id(s.GetStudentId()))
{
    studentId->SetStudent(this);  // create back link
    numStudents++;
}

// destructor definition
Student::~Student()
{
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

void Student::IsA() const
{
    cout << "Student" << endl;
}

const string &Student::GetStudentId() const 
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

