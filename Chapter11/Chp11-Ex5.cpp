// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a user defined exception class derived from exception

#include <iostream>
#include <iomanip>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::set_terminate;
using std::string;
using std::to_string;
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
    int errCode = 0;  // in-class initialization (will be over written with bonified value after successful alt constructor)
    string details;
public:   
    StudentException(const string &det, int num): errCode(num), details(det) { }   
    virtual ~StudentException() = default; 
    const char *what() const throw() override   // note: what() returns a const char * (we must override with the same signature)
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
    char middleInitial = '\0';  // in-class initialization -- value to be used in default constructor
    string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
    void ModifyTitle(const string &);
public:
    Person() = default;   // default constructor
    Person(const string &, const string &, char, const string &);
    Person(const Person &) = default;  // copy constructor
    virtual ~Person() = default;  // virtual destructor

    // inline function definitions
    const string &GetFirstName() const { return firstName; }
    const string &GetLastName() const { return lastName; }
    const string &GetTitle() const { return title; }
    char GetMiddleInitial() const { return middleInitial; }

    // Virtual functions will (usually) not be inlined since their method must be determined at run time using v-table (except rare cases)
    virtual void Print() const;
    virtual void IsA() const;
    virtual void Greeting(const string &) const;
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

// We're using default destructor, but if you wanted to write it yourself, this is what it would look like:
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
    float gpa = 0.0;   // in-class initialization
    string currentCourse;
    const string studentId;
    static int numStudents; // static data member is initialized outside of class (see below)
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &);
    Student(const Student &);  // copy constructor
    ~Student() override;  // destructor
    void EarnPhD();
    bool TakePrerequisites();   // new member function
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only

    // In the derived class, the keyword virtual is optional for overridden (polymorphic) methods, as is the keyword "override"
    // Currently, "override" is recommended for internal documentation, however "virtual" is not recommended
    void Print() const override;
    void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &) const
    virtual void Validate();  // newly introduced virtual functions in Student
    virtual void Graduate();

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
   // Also, remember to dynamically allocate memory for any pointer data members here (not needed in this example)
   numStudents++;
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id) : Person(fn, ln, mi, t),
                       gpa(avg), currentCourse(course), studentId(id)
{
   // dynamically allocate memory for any pointer data members here
   numStudents++;
}

// Copy constructor definition
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

