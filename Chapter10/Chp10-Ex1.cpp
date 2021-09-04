// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate aggregation (composition) of objects
// modelled via a data member.For each student, a unique id exists.  
// We'll assume that an id always exists for a given student. 
// Both the student and id are implemented as objects.  
// The Student object will contain an embedded object
// for id to model the aggregation (composition).

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

class Id
{
private:
   string idNumber;
public:
   Id() = default;   // we do want this interface for construction
   Id(const string &id) : idNumber(id) { }
   Id(const Id &) = default;
   ~Id() = default;
   const string &GetId() const { return idNumber; }
};

// We're using the default copy constructor, but if you wrote it yourself, this is what it would look like:
/*
Id::Id(const Id &id) : idNumber(id.idNumber)
{
}
*/

class Person
{
private: 
    // data members
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

    // Virtual functions 
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
}

// We're using default copy constructor, but if you wrote it, this is what it would look like:
/*
Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), 
                                  middleInitial(p.middleInitial), title(p.title)
{
}
*/

// We're using default destructor, but if you wrote it, here's what it would look like:
/*
Person::~Person()
{
}
*/

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
    float gpa = 0.0;    // in-class initializataion
    string currentCourse;
    static int numStudents;
    Id studentId;  // part 
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &); 
    Student(const Student &);  // copy constructor
    ~Student() override;  // destructor
    void EarnPhD();  
    float GetGpa() const { return gpa; }  // various inline fns.
    const string &GetCurrentCourse() const { return currentCourse; }
    void SetCurrentCourse(const string &); // prototype only
    void Print() const override;
    void IsA() const override;
    static int GetNumberStudents() { return numStudents; }
    
    // Access function for associated Id object
    const string &GetStudentId() const; // prototype only 
};

int Student::numStudents = 0;  // definition of static data member


inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student() : studentId (to_string(numStudents + 100) + "Id")   // set studentId with manufactured id 
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course,
                 const string &id) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
{
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
    numStudents++;
}
   
// destructor definition
Student::~Student()
{
    numStudents--;
    // the embedded object studentId will also be destructed
}

void Student::EarnPhD()
{
    ModifyTitle("Dr.");  
}

void Student::Print() const
{   
    cout << GetTitle() << " " << GetFirstName() << " ";
    cout << GetMiddleInitial() << ". " << GetLastName();
    cout << " with id: " << studentId.GetId() << " GPA: ";
    cout << setprecision(3) <<  " " << gpa;
    cout << " Course: " << currentCourse << endl;
}

void Student::IsA() const
{
    cout << "Student" << endl;
}

const string &Student::GetStudentId() const 
{ 
    return studentId.GetId(); 
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

