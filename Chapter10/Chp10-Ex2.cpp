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

constexpr int MAX = 25;

class Student; // forward declaration 

class University
{
private:
   string name;
   // Association to many students
   Student *studentBody[MAX];  
   int currentNumStudents;
public:
   University();
   University(const string &);
   University(const University &) = delete;  // prohibit copies
   ~University();
   void EnrollStudent(Student *);
   const string &GetName() const { return name; }
   void PrintStudents() const;
};

University::University() : name(""), currentNumStudents(0)
{
   for (int i = 0; i < MAX; i++)
      studentBody[i] = nullptr;  
}

University::University(const string &n) : name(n), currentNumStudents(0)
{
   for (int i = 0; i < MAX; i++)
      studentBody[i] = nullptr;  
}

University::~University()
{
   // The students will delete themselves
   // but we can null out our pointers to them
   for (int i = 0; i < MAX; i++)
      studentBody[i] = nullptr; 
}

void University::EnrollStudent(Student *s)
{
   studentBody[currentNumStudents++] = s;
}

class Id
{
private:
   string idNumber;
public:
   Id() : idNumber("") { }
   Id(const string &); 
   Id(const Id &);  
   ~Id() { }
   const string &GetId() const { return idNumber; }
};

Id::Id(const string &id) : idNumber(id)
{
}

Id::Id(const Id &id) : idNumber(id.idNumber) 
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

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial), title(p.title)
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
    Id studentId;  // part 
    University *univ;  // Association to University object
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &, University *); 
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
    const string &GetStudentId() const { return studentId.GetId(); }
    const string &GetUniversity() const { return univ->GetName(); }
};

int Student::numStudents = 0;  // definition of static data member


inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c; 
}

Student::Student() : gpa(0.0), currentCourse(""), studentId ("None"), univ(nullptr) 
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

