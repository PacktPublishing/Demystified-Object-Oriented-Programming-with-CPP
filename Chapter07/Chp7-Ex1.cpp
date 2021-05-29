// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate polymorphism in C++ with virtual functions.

#include <iostream>
#include <iomanip>

using std::cout;    //preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;

constexpr int MAX = 5;

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
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only
  
    // In the derived class, the keyword virtual is optional, 
    // but recommended for internal documentation
    virtual void Print() const final override;  // final indicates this may not be overridden beyond Student
    virtual void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &) const
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

int main()
{
    Person *people[MAX] = { nullptr, nullptr, nullptr, nullptr, nullptr };

    people[0] = new Person("Juliet", "Martinez", 'M', "Ms.");
    people[1] = new Student("Hana", "Sato", 'U', "Dr.", 3.8,
                            "C++", "178PSU"); 
    people[2] = new Student("Sara", "Kato", 'B', "Dr.", 3.9,
                            "C++", "272PSU"); 
    people[3] = new Person("Giselle", "LeBrun", 'R', "Miss");
    people[4] = new Person("Linus", "Van Pelt", 'S', "Mr.");

    for (int i = 0; i < MAX; i++)
    {
       people[i]->IsA();
       cout << "  ";
       people[i]->Print();
    } 

    for (int i = 0; i < MAX; i++)
       delete people[i];   // engage virtual dest. sequence

    return 0;
}

