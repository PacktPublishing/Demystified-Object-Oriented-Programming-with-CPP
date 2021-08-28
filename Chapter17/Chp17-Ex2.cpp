// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate an alternate implmenentation of the Factory Method Pattern
// Implemented with the Factory Method in an Object Factory Class. 
// Here, the Product of the Factory Method is Student. 
// Concrete Products are GraduateStudent, UnderGraduateStudent, NonDegreeStudent

#include <iostream>
#include <iomanip>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;

constexpr int MAX = 3;

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

    const string &GetFirstName() const { return firstName; }
    const string &GetLastName() const { return lastName; }
    const string &GetTitle() const { return title; }
    char GetMiddleInitial() const { return middleInitial; }

    virtual void Print() const;
    virtual string IsA() const;
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

string Person::IsA() const
{
    return "Person";
}

void Person::Greeting(const string &msg) const
{
    cout << msg << endl;
}


// Student is now an Abstract class (see pure virtual Graduate() method)
// MatriculateStudent() is the Factory Method (Creation)
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
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only

    // In the derived class, the keyword virtual is optional,
    // but recommended for internal documentation
    virtual void Print() const override;
    virtual string IsA() const override { return "Student"; }
    // note: we choose not to redefine Person::Greeting(const string &) const

    virtual void Graduate() = 0;  // Now Student is abstract
};

inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student() : gpa(0.0), currentCourse(""), studentId ("")
{
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &course, const string &id) :
                 Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
{
}

// Copy constructor definition
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
}

// destructor definition
Student::~Student()
{
}

void Student::Print() const
{   // need to use access functions as these data members are
    // defined in Person as private
    cout << "  " << GetTitle() << " " << GetFirstName() << " ";
    cout << GetMiddleInitial() << ". " << GetLastName();
    cout << " with id: " << studentId << " GPA: ";
    cout << setprecision(3) <<  " " << gpa;
    cout << " Course: " << currentCourse << endl;
}

class GradStudent : public Student
{
private:
    string degree;  // PhD, MS, MA, etc.
public:
    // member function prototypes
    GradStudent(): degree("") { }  // default constructor
    GradStudent(const string &, const string &, const string &, char, const string &, float, const string &, const string &);
    GradStudent(const GradStudent &);  // copy constructor
    virtual ~GradStudent() { } // destructor
    void EarnPhD();
    virtual string IsA() const override { return "GradStudent"; }
    virtual void Graduate() override;
};

// Alternate constructor member function definition
GradStudent::GradStudent(const string &deg, const string &fn, const string &ln, char mi,
                 const string &t, float avg, const string &course, const string &id) :
                 Student(fn, ln, mi, t, avg, course, id), degree(deg)
{
}

// Copy constructor definition
GradStudent::GradStudent(const GradStudent &gs) : Student(gs), degree(gs.degree)
{
}

void GradStudent::EarnPhD()
{
    if (!degree.compare("PhD"))   // only PhD candidates can EarnPhD()
        ModifyTitle("Dr.");       // not MA and MS candidates
}

void GradStudent::Graduate()
{
    // Here, we can check that the required number of credits
    // have been met with a passing gpa, and that their
    // doctoral or master’s thesis has been completed.
    EarnPhD();
    cout << "GradStudent::Graduate()" << endl;
}

class UnderGradStudent : public Student
{
private:
    string degree;  // BS, BA, etc
public:
    // member function prototypes
    UnderGradStudent() : degree("") { }  // default constructor
    UnderGradStudent(const string &, const string &, const string &, char, const string &,
                     float, const string &, const string &);
    UnderGradStudent(const UnderGradStudent &);  // copy constructor
    virtual ~UnderGradStudent() { } // destructor
    virtual string IsA() const override { return "UnderGradStudent"; }
    virtual void Graduate() override;
};

// Alternate constructor member function definition
UnderGradStudent::UnderGradStudent(const string &deg, const string &fn, const string &ln, char mi,
                 const string &t, float avg, const string &course, const string &id) :
                 Student(fn, ln, mi, t, avg, course, id), degree(deg)
{
}

// Copy constructor definition
UnderGradStudent::UnderGradStudent(const UnderGradStudent &gs) : Student(gs), degree(gs.degree)
{
}

void UnderGradStudent::Graduate()
{
    // Verify that number of credits and gpa requirements have
    // been met for major and any minors or concentrations.
    // Have all applicable university fees been paid?
    cout << "UnderGradStudent::Graduate()" << endl;
}

class NonDegreeStudent : public Student
{
private:
public:
    // member function prototypes
    NonDegreeStudent() { }  // default constructor
    NonDegreeStudent(const string &, const string &, char, const string &, float, const string &, const string &);
    NonDegreeStudent(const NonDegreeStudent &s): Student(s) { }  // copy constructor
    virtual ~NonDegreeStudent() { } // destructor
    virtual string IsA() const override { return "NonDegreeStudent"; }
    virtual void Graduate() override;
};

// Alternate constructor member function definition
NonDegreeStudent::NonDegreeStudent(const string &fn, const string &ln, char mi,
                 const string &t, float avg, const string &course, const string &id) :
                 Student(fn, ln, mi, t, avg, course, id)
{
}

void NonDegreeStudent::Graduate()
{
    // Check if applicable tuition has been paid.
    // There is no credit or gpa requirement.
    cout << "NonDegreeStudent::Graduate()" << endl;
}

class StudentFactory
{
public:
    // Creates a student based on the degree they seek
    Student *MatriculateStudent(const string &degree, const string &fn, const string &ln, char mi,
                                const string &t, float avg, const string &course, const string &id)
    {
    if (!degree.compare("PhD") || !degree.compare("MS") || !degree.compare("MA"))
        return new GradStudent(degree, fn, ln, mi, t, avg, course, id);
    else if (!degree.compare("BS") || !degree.compare("BA"))
        return new UnderGradStudent(degree, fn, ln, mi, t, avg, course, id);
    else if (!degree.compare("None"))
        return new NonDegreeStudent(fn, ln, mi, t, avg, course, id);
    }

};


int main()
{
    Student *scholars[MAX] = { nullptr, nullptr, nullptr };
    StudentFactory *UofD = new StudentFactory();

    // Student is now abstract....can not instantiate directly
    // Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"); 

    scholars[0] = UofD->MatriculateStudent("PhD", "Sara", "Kato", 'B', "Ms.", 3.9, "C++", "272PSU"); 
    scholars[1] = UofD->MatriculateStudent("BS", "Ana", "Sato", 'U', "Ms.", 3.8, "C++", "178PSU"); 
    scholars[2] = UofD->MatriculateStudent("None", "Elle", "LeBrun", 'R', "Miss", 3.5, "c++", "111BU");

    for (int i = 0; i < MAX; i++)
    {
       scholars[i]->Graduate();
       scholars[i]->Print();
    } 
    for (int i = 0; i < MAX; i++)
       delete scholars[i];   // engage virtual dest. sequence

    return 0;
}

