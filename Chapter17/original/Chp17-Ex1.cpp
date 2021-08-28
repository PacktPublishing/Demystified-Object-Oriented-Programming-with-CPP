// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate Factory Method Pattern
// Implemented with Factory Method in the Abstract (Product) Class
// Here, the Product of the Factory Method is Student. 
// Concrete Products are GraduateStudent, UnderGraduateStudent, NonDegreeStudent

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX = 3;

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
    virtual const char *IsA();  
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

const char *Person::IsA()
{
    return "Person";
}

void Person::Greeting(const char *msg)
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
    char *currentCourse;
    const char *studentId;  
public:
    // member function prototypes
    Student();  // default constructor
    Student(const char *, const char *, char, const char *,
            float, const char *, const char *); 
    Student(const Student &);  // copy constructor
    virtual ~Student();  // destructor
    // inline function definitions
    float GetGpa() const { return gpa; }
    const char *GetCurrentCourse() const { return currentCourse; }
    const char *GetStudentId() const { return studentId; }
    void SetCurrentCourse(const char *); // prototype only
  
    // In the derived class, the keyword virtual is optional, 
    // but recommended for internal documentation
    virtual void Print() const override;
    virtual const char *IsA() override { return "Student"; }
    // note: we choose not to redefine Person::Greeting(const char *)

    virtual void Graduate() = 0;  // Now Student is abstract
    // Creates a derived Student type based on the degree the seek
    static Student *MatriculateStudent(const char *degree, const char *fn, const char *ln, char mi, 
                                       const char *t, float avg, const char *course, const char *id); 
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
    char *degree;  // PhD, MS, MA, etc.
public:
    // member function prototypes
    GradStudent() { degree = 0; }  // default constructor
    GradStudent(const char *, const char *, const char *, char, const char *,
                float, const char *, const char *); 
    GradStudent(const GradStudent &);  // copy constructor
    virtual ~GradStudent() { delete degree; } // destructor
    void EarnPhD();  
    virtual const char *IsA() override { return "GradStudent"; }
    virtual void Graduate() override; 
};

// Alternate constructor member function definition
GradStudent::GradStudent(const char *deg, const char *fn, const char *ln, char mi, 
                 const char *t, float avg, const char *course,
                 const char *id) : Student(fn, ln, mi, t, avg, course, id)
{
    degree = new char [strlen(deg) + 1];
    strcpy(degree, deg);
}

// Copy constructor definition
GradStudent::GradStudent(const GradStudent &gs) : Student(gs)
{
    degree = new char [strlen(gs.degree) + 1];
    strcpy(degree, gs.degree);
}

void GradStudent::EarnPhD()
{
    if (!strcmp(degree, "PhD"))   // only PhD candidates can EarnPhD()
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
    char *degree;  // BS, BA, etc 
public:
    // member function prototypes
    UnderGradStudent() { degree = 0; }  // default constructor
    UnderGradStudent(const char *, const char *, const char *, char, const char *,
                     float, const char *, const char *); 
    UnderGradStudent(const UnderGradStudent &);  // copy constructor
    virtual ~UnderGradStudent() { delete degree; } // destructor
    virtual const char *IsA() override { return "UnderGradStudent"; }
    virtual void Graduate() override; 
};

// Alternate constructor member function definition
UnderGradStudent::UnderGradStudent(const char *deg, const char *fn, const char *ln, char mi, 
                 const char *t, float avg, const char *course,
                 const char *id) : Student(fn, ln, mi, t, avg, course, id)
{
    degree = new char [strlen(deg) + 1];
    strcpy(degree, deg);
}

// Copy constructor definition
UnderGradStudent::UnderGradStudent(const UnderGradStudent &gs) : Student(gs)
{
    degree = new char [strlen(gs.degree) + 1];
    strcpy(degree, gs.degree);
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
    NonDegreeStudent(const char *, const char *, char, const char *,
                     float, const char *, const char *); 
    NonDegreeStudent(const NonDegreeStudent &s): Student(s) { }  // copy constructor
    virtual ~NonDegreeStudent() { } // destructor
    virtual const char *IsA() override { return "NonDegreeStudent"; }
    virtual void Graduate() override; 
};

// Alternate constructor member function definition
NonDegreeStudent::NonDegreeStudent(const char *fn, const char *ln, char mi, 
                 const char *t, float avg, const char *course,
                 const char *id) : Student(fn, ln, mi, t, avg, course, id)
{
}

void NonDegreeStudent::Graduate()
{
    // Check if applicable tuition has been paid. 
    // There is no credit or gpa requirement.
    cout << "NonDegreeStudent::Graduate()" << endl;
}

// Creates a student based on the degree they seek
Student *Student::MatriculateStudent(const char *degree, const char *fn, const char *ln, char mi, 
                                     const char *t, float avg, const char *course, const char *id)    
{
    if (!strcmp(degree, "PhD") || !strcmp(degree, "MS") || !strcmp(degree, "MA"))
        return new GradStudent(degree, fn, ln, mi, t, avg, course, id);
    else if (!strcmp(degree, "BS") || !strcmp(degree, "BA"))
        return new UnderGradStudent(degree, fn, ln, mi, t, avg, course, id);
    else if (!strcmp(degree, "None")) 
        return new NonDegreeStudent(fn, ln, mi, t, avg, course, id);
}


int main()
{
    Student *scholars[MAX];

    // Student is now abstract....can not instantiate directly
    // Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"); 

    scholars[0] = Student::MatriculateStudent("PhD", "Sara", "Kato", 'B', "Ms.", 3.9, "C++", "272PSU"); 
    scholars[1] = Student::MatriculateStudent("BS", "Ana", "Sato", 'U', "Ms.", 3.8, "C++", "178PSU"); 
    scholars[2] = Student::MatriculateStudent("None", "Elle", "LeBrun", 'R', "Miss", 3.5, "C++", "111BU");

    for (int i = 0; i < MAX; i++)
    {
       scholars[i]->Graduate();
       scholars[i]->Print();
    } 
    for (int i = 0; i < MAX; i++)
       delete scholars[i];   // engage virtual dest. sequence

    return 0;
}

