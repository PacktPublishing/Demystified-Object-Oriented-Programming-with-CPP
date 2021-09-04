// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate a 1-many association.
// A University is associated to many students.  
// In this case, let's assume, each student has 
// an association to a single university. 

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 25;

class Student; // forward declaration 

class University
{
private:
   string name;
   // Association to many students
   Student *studentBody[MAX];    // pointers will be nulled out in constructors with nullptr
   int currentNumStudents = 0;   // in-class initialization
public:
   University();
   University(const string &);
   University(const University &) = delete;  // prohibit copies
   ~University();
   void EnrollStudent(Student *);
   const string &GetName() const { return name; }
   void PrintStudents() const;
};

// Remember, currentNumStudents is set with in-class initialization and name, as a string member object is constructed as empty
University::University() 
{
   for (int i = 0; i < MAX; i++)    // let's set each to nullptr for safety 
      studentBody[i] = nullptr;  
}

University::University(const string &n) : name(n)   // remember, currentNumStudents is set with in-class init
{
   for (int i = 0; i < MAX; i++)   // let's set each to nullptr
      studentBody[i] = nullptr;  
}

University::~University()
{
   // The students will delete themselves, but we can null out our pointers to them!
   for (int i = 0; i < MAX; i++)
      studentBody[i] = nullptr; 
}

void University::EnrollStudent(Student *s)
{
   // ideally, we'd add many checks here -- duplicate enrollment, exceeding size of student body, etc.
   studentBody[currentNumStudents++] = s;
}


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
Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title)
{
}
*/

// We're using default destructor, but if you wrote it, this is what it would look like:
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
    University *univ = nullptr;  // Association to University object, set with in-class initialization
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &, University *); 
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
    const string &GetStudentId() const { return studentId.GetId(); }
    const string &GetUniversity() const { return univ->GetName(); }
};

int Student::numStudents = 0;  // definition of static data member


inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c; 
}

// Remember, gpa and univ are set with in-class initialization and name (member string) will be constructed with an empty string
Student::Student() : studentId (to_string(numStudents + 100) + "Id")   // set studentId with manufactured id
{
    numStudents++;
}

Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course,
                 const string &id, University *univ) : Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
{
    this->univ = univ;  // demonstrating a required use of 'this' to set forward link -- data member and parameter have same identifiers
    univ->EnrollStudent(this);  // another required use of 'this' to create the back link
    numStudents++;
}

Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
    this->univ = s.univ;   // set forward link -- forward link could also be set in mbr init list if param name is changed
    univ->EnrollStudent(this);   // create back link
    numStudents++;
}
   
// destructor definition
Student::~Student()
{
    numStudents--;
    univ = nullptr;  // the University will delete itself
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

void University::PrintStudents() const
{
   cout << name << " has the following students:" << endl;
   for (int i = 0; i < currentNumStudents; i++)
   {
      cout << "\t" << studentBody[i]->GetFirstName() << " ";
      cout << studentBody[i]->GetLastName() << endl;
   }
} 

int main()
{
    University u1("The George Washington University");
    Student s1("Gabby", "Doone", 'A', "Miss", 3.85, "C++", "4225GWU", &u1); 
    Student s2("Giselle", "LeBrun", 'A', "Ms.", 3.45, "C++", "1227GWU", &u1); 
    Student s3("Eve", "Kendall", 'B', "Ms.", 3.71, "C++", "5542GWU", &u1); 

    cout << s1.GetFirstName() << " " << s1.GetLastName() << " attends "; 
    cout << s1.GetUniversity() << endl;

    cout << s2.GetFirstName() << " " << s2.GetLastName() << " attends "; 
    cout << s2.GetUniversity() << endl;

    cout << s3.GetFirstName() << " " << s3.GetLastName() << " attends "; 
    cout << s3.GetUniversity() << endl;

    u1.PrintStudents();
    return 0;
}

