// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a user defined exception class derived from exception

#include <iostream>
#include <iomanip>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::set_terminate;
using std::string;
using std::exception; 

constexpr int MAX = 5;

void AppSpecificTerminate()
{
    cout << "Uncaught exception. Program terminating" << endl;
    exit(1);
}

class StudentException: public exception
{
private:
    int errCode;  
    string details;
public:   
    StudentException(const string &det, int num): errCode(num), details(det) { }   
    virtual ~StudentException() { }
    virtual const char *what() const throw()    // note: what() returns a const char * (we must override with the same signature)
    {
        return "Student Exception";
    }
    int GetCode() const { return errCode; }
    const string &GetDetails() const { return details; }
};

class Person
{
private:
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

    // Virtual functions will not be inlined since their
    // method must be determined at run time using v-table.
    virtual void Print() const;
    virtual void IsA() const;
    virtual void Greeting(const string &) const;
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

class Student : public Person
{
private:
    // data members
    float gpa;
    string currentCourse;
    const string studentId;
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);  // copy constructor
    virtual ~Student();  // destructor
    void EarnPhD();
    bool TakePrerequisites();   // new member function
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only

    // In the derived class, the keyword virtual is optional,
    // but recommended for internal documentation
    virtual void Print() const override;
    virtual void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &) const
    virtual void Validate();  // newly introduced virtual function in Student
    virtual void Graduate();
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
Student::Student(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id) : Person(fn, ln, mi, t),
                       gpa(avg), currentCourse(course), studentId(id)
{
   // dynamically allocate memory for any pointer data members here
}

// Copy constructor definition
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

void Student::EarnPhD()
{
    ModifyTitle("Dr.");  
}

void Student::Print() const
{   // need to use access functions as these data members are
    // defined in Person as private
    cout << GetTitle() << " " << GetFirstName() << " ";
    cout << GetMiddleInitial() << ". " << GetLastName();
    cout << " with id: " << studentId << " GPA: ";
    cout << setprecision(3) <<  " " << gpa;
    cout << " Course: " << currentCourse << endl;
}

void Student::IsA() const
{
    cout << "Student" << endl;
}

void Student::Validate()
{
    // check Student instance to see if standards are met; if not, throw an exception
    throw string("Student does not meet prerequisites"); 
}

bool Student::TakePrerequisites()
{
    // Assume this function can correct the issue at hand
    // if not, it returns false
    return false;
}

void Student::Graduate()
{
   // if something goes wrong, instantiate a StudentException,
   // pack it with relevant data during construction, and then
   // throw the dereferenced pointer as a referenceable object
   throw *(new StudentException("Missing Credits", 4));
}


int main()
{
    set_terminate(AppSpecificTerminate);  // register fn.

    Student s1("Alexandra", "Doone", 'G', "Miss", 3.95, "C++", "231GWU"); 

    try
    {
        s1.Graduate();
    }
    catch (const StudentException &e)  // catch the exception by ref
    { 
        cout << e.what() << endl;
        cout << e.GetCode() << " " << e.GetDetails() << endl;
        // Grab useful info from e and try to fix the problem
        // if we can fix the problem, and continue the application,
        // be sure to deallocate heap memory for e using:
        // delete &e;  // take the addr of the ref
        exit(1);  // only exit if necessary!  Memory will be reclaimed upon exit.
    }


    cout << "Moving onward with remainder of code." << endl;

    return 0;
}

