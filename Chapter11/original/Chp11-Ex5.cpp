// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a user defined exception class derived from exception

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX = 5;

void AppSpecificTerminate()
{
    cout << "Uncaught exception. Program terminating" << endl;
    exit(1);
}

class StudentException: public exception
{
private:
    int errCode;  
    char *details;
public:   
    StudentException(const char *det, int num): errCode(num)
    {
        details = new char[strlen(det) + 1];
        strcpy(details, det);
    }   
    virtual ~StudentException() { delete details; }
    virtual const char *what() const throw()
    {
        return "Student Exception";
    }
    int GetCode() const { return errCode; }
    const char *GetDetails() const { return details; }
};

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

    // Virtual functions will not be inlined since their 
    // method must be determined at run time using v-table.
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

class Student : public Person
{
private: 
    // data members
    float gpa;
    char *currentCourse;
    const char *studentId;  
public:
    // member function prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, const char *,
            float, const char *, const char *); 
    Student(const Student &);  // copy constructor
    virtual ~Student();  // destructor
    void EarnPhD();  
    bool TakePrerequisites();
    // inline function definitions
    float GetGpa() const { return gpa; }
    const char *GetCurrentCourse() const { return currentCourse; }
    const char *GetStudentId() const { return studentId; }
    void SetCurrentCourse(const char *); // prototype only
  
    // In the derived class, the keyword virtual is optional, 
    // but recommended for internal documentation
    virtual void Print() const override;
    virtual void IsA() override;
    // note: we choose not to redefine 
    // Person::Greeting(const char *)
    virtual void Validate();  // newly introduced virtual fn in Student
    virtual void Graduate();
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
Student::Student(const char *fn, const char *ln, char mi, 
                 const char *t, float avg, const char *course,
                 const char *id) : Person(fn, ln, mi, t)
{
    gpa = avg;
    currentCourse = new char [strlen(course) + 1];
    strcpy(currentCourse, course);
    char *temp = new char [strlen(id) + 1];
    strcpy (temp, id); 
    studentId = temp;
}

// Copy constructor definition
Student::Student(const Student &ps) : Person(ps)
{
    gpa = ps.gpa;
    currentCourse = new char [strlen(ps.currentCourse) + 1];
    strcpy(currentCourse, ps.currentCourse);
    char *temp = new char [strlen(ps.studentId) + 1];
    strcpy (temp, ps.studentId); 
    studentId = temp;
}
   
// destructor definition
Student::~Student()
{
    delete currentCourse;
    delete (char *) studentId;
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

void Student::IsA()
{
    cout << "Student" << endl;
}

void Student::Validate()
{
    // check Student instance to see if standards are met; if not, throw an exception
    throw "Student does not meet prerequisites"; 
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

