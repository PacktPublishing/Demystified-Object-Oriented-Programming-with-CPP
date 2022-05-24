// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Sample Solution (polymorphism) for Chp. 7, question 1, parts a - e 

#include <iostream>
#include <iomanip>

using std::cout;    //preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 5;

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
    Person(const Person &);  // copy constructor
    virtual ~Person();   // virtual destructor

    // inline function definitions
    const string &GetFirstName() const { return firstName; }    // firstName returned as const string 
    const string &GetLastName() const { return lastName; }      // so is lastName (via implicit cast)
    const string &GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }

    // Virtual functions will not be inlined since their method must be determined at run time using v-table.
    virtual void Print() const;
    virtual void IsA() const;  
    virtual void Greeting(const string &) const;
};

// With in-class initialization, writing the default constructor yourself is no longer necessary
// Here's how it would look if you did choose to provide one (and also chose not to use in-class initialization)
/*
Person::Person() : middleInitial('\0')
{
   cout << "Person default constructor" << endl;
   // Remember, string members are automatically initialized to empty with the default string constructor
   // dynamically allocate memory for any pointer data members here
}
*/

Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
   cout << "Person alternate constructor" << endl;
   // dynamically allocate memory for any pointer data members here
}

// Here we're writing the copy constructor just so we can add a print statement to trace its usage
Person::Person(const Person &p) :
               firstName(p.firstName), lastName(p.lastName),
               middleInitial(p.middleInitial), title(p.title)
{
   cout << "Person copy constructor" << endl;
   // deep copy any pointer data members here
}

// Simple destructor written ourselves, just so we can trace the destructor chain using cout statements 
Person::~Person()
{
   // release memory for any dynamically allocated data members
   cout << "Person destructor <" << firstName << " " << lastName << ">" << endl;
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


// Now, since we are specializing a Student (below) with a GraduateStudent, we will re-design our class to move EarnPhd() 
// to the GraduateStudent level instead. Typically, this would be done at design time, not during implementation
class Student : public Person
{
private: 
    // data members
    float gpa = 0.0;    // in-class initializataion
    string currentCourse;
    const string studentId;  
    static int numStudents;  // static data member is initialized outside of class (see below)
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &); 
    Student(const Student &);  // copy constructor
    ~Student() override;  // This is a virtual destructor; override indicates 'entry' point in destruction sequence 

    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only
  
    // In the derived class, the keyword virtual is optional for overridden (polymorphic) methods, as is the keyword "override"
    // Currently, "override" is recommended for internal documentation, however "virtual" is not recommended
    void Print() const final override;  // final indicates this may not be overridden beyond Student
    void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &) const

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
   cout << "Student default constructor" << endl;
   numStudents++;
}


// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id) : Person(fn, ln, mi, t),
                       gpa(avg), currentCourse(course), studentId(id)
{
   // dynamically allocate memory for any pointer data members here
   cout << "Student alternate constructor" << endl;
   numStudents++;
}

// Copy constructor definition
Student::Student(const Student &s) : Person(s),
                 gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
   // deep copy any pointer data members of derived class here
   cout << "Student copy constructor" << endl;
   numStudents++;

}

// destructor definition
Student::~Student()
{
   // release memory for any dynamically allocated data members
   numStudents--;
   cout << "Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << endl;
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

class GraduateStudent : public Student
{
private: 
    // data members
    string advisor;
    string degreeInProgress;
    string dissertationTopic;
public:
    // member function prototypes
    GraduateStudent() = default;  // default constructor
    GraduateStudent(const string &, const string &, char, const string &, float, const string &, const string &, const string &, const string &, const string &); 
    GraduateStudent(const GraduateStudent &);  // copy constructor
    ~GraduateStudent() override;  // This is a virtual destructor; override indicates 'entry' point in destruction sequence 

    void EarnPhD();  
    void SetAdvisor(const string &adv) { advisor = adv; } // allow Grad Student to change their advisor
    const string &GetAdvisor() const { return advisor; }
    void SetDegree(const string &degree)  { degreeInProgress = degree; } // allow student to change their saught after degree
    const string &GetDegree() const { return degreeInProgress; }
    void SetDissertationTopic(const string &topic)  { dissertationTopic = topic; } // allow student to change their research topic
    const string &GetTopic() const { return dissertationTopic; }
  
    // In the derived class, the keyword virtual is optional for overridden (polymorphic) methods, as is the keyword "override"
    // Currently, "override" is recommended for internal documentation, however "virtual" is not recommended
    void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &) const
    // note: we can not override Print(), as it was final in Student -- certainly, this is a design issue -- was it the correct choice?
};


// Note that default constructor is fine as supplied - all of the additional data members are strings and will be default constructed
// The default constructor will invoke the Student constructor under the hood (which in turn will invoke the Person Constructor)


// Alternate constructor member function definition
GraduateStudent::GraduateStudent(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id, const string &adv, const string &degree, const string &topic) : 
                                      Student(fn, ln, mi, t, avg, course, id), advisor(adv), degreeInProgress(degree), dissertationTopic(topic)
{
   cout << "Graduate Student alternate constructor" << endl;
   // dynamically allocate memory for any pointer data members here
}

// Copy constructor definition
// The default definition for the copy constructor was adequate, yet, we wanted to add a print statement, so we wrote method ourselves 
GraduateStudent::GraduateStudent(const GraduateStudent &s) : Student(s),
                 advisor(s.advisor), degreeInProgress(s.degreeInProgress), dissertationTopic(s.dissertationTopic)
{
   // deep copy any pointer data members of derived class here
   cout << "Graduate Student copy Constructor" << endl;

}

// destructor definition
GraduateStudent::~GraduateStudent()
{
   // release memory for any dynamically allocated data members
   cout << "Graduate Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << endl;
}

void GraduateStudent::EarnPhD()
{
    if (degreeInProgress == "PhD")   // only PhD candidates can earn a PhD
       ModifyTitle("Dr.");  
    else
       cout << "Only PhD candidates can earn a PhD" << endl;
}

void GraduateStudent::IsA() const
{
    cout << "Graduate Student" << endl;
}

class NonDegreeStudent : public Student
{
private: 
    // data members
    string learningPath;
public:
    // member function prototypes
    NonDegreeStudent() = default;  // default constructor
    NonDegreeStudent(const string &, const string &, char, const string &, float, const string &, const string &, const string &); 
    NonDegreeStudent(const NonDegreeStudent &);  // copy constructor
    ~NonDegreeStudent() override;  // This is a virtual destructor; override indicates 'entry' point in destruction sequence 

    void SetPath(const string &path) { learningPath = path; } // allow student to change their learning path 
    const string &GetPath() const { return learningPath; }
  
    // In the derived class, the keyword virtual is optional for overridden (polymorphic) methods, as is the keyword "override"
    // Currently, "override" is recommended for internal documentation, however "virtual" is not recommended
    void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &) const
    // note: we can not override Print(), as it was final in Student -- certainly, this is a design issue -- was it the correct choice?
};


// Note that default constructor is fine as supplied - all of the additional data members are strings and will be default constructed
// The default constructor will invoke the Student constructor under the hood (which in turn will invoke the Person Constructor)


// Alternate constructor member function definition
NonDegreeStudent::NonDegreeStudent(const string &fn, const string &ln, char mi, const string &t,
       float avg, const string &course, const string &id, const string &path) : 
                                      Student(fn, ln, mi, t, avg, course, id), learningPath(path) 
{
   cout << "Non Degree Student alternate constructor" << endl;
   // dynamically allocate memory for any pointer data members here
}

// Copy constructor definition
// The default definition for the copy constructor was adequate, yet, we wanted to add a print statement, so we wrote method ourselves 
NonDegreeStudent::NonDegreeStudent(const NonDegreeStudent &s) : Student(s),
                 learningPath(s.learningPath)
{
   // deep copy any pointer data members of derived class here
   cout << "Non Degree Student copy constructor" << endl;

}

// destructor definition
NonDegreeStudent::~NonDegreeStudent()
{
   // release memory for any dynamically allocated data members
   cout << "Non Degree Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << endl;
}

void NonDegreeStudent::IsA() const
{
    cout << "Non Degree Student" << endl;
}

int main()
{
    Person *people[MAX] = { };  // will be initialized to nullptrs

    people[0] = new Person("Juliet", "Martinez", 'M', "Ms.");
    people[1] = new Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU"); 
    people[2] = new Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"); 
    people[3] = new GraduateStudent("Giselle", "LeBrun", 'R', "Miss", 3.5, "C++", "123TU", "Prof. Korsh", "M.S.", "Distributed Programming");
    people[4] = new NonDegreeStudent("Linus", "Van Pelt", 'S', "Mr.", 3.6, "Environmental Science", "234UD", "Climate Change");

    // We will soon see a more modern way to use for loops (range for)
    for (int i = 0; i < MAX; i++)
    {
       people[i]->IsA();
       cout << "  ";
       people[i]->Print();
    } 

    for (int i = 0; i < MAX; i++)
       delete people[i];   // engage virtual dest. sequence

    cout << endl;

    Student *learners[MAX] = { };  // will be initialized to nullptrs

    learners[0] = new Student("Juliet", "Martinez", 'M', "Ms.", 3.5, "Adv C++", "456UD");
    learners[1] = new Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU"); 
    learners[2] = new GraduateStudent("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU", "Prof. Kwatney", "PhD", "Operating Systems"); 
    learners[3] = new GraduateStudent("Giselle", "LeBrun", 'R', "Miss", 3.5, "C++", "123TU", "Prof. Korsh", "M.S.", "Distributed Programming");
    learners[4] = new NonDegreeStudent("Linus", "Van Pelt", 'S', "Mr.", 3.6, "Environmental Science", "234UD", "Climate Change");

    // We will soon see a more modern way to use for loops (range for)
    for (int i = 0; i < MAX; i++)
    {
       learners[i]->IsA();
       cout << "  ";
       cout << learners[i]->GetFirstName() << learners[i]->GetLastName() << learners[i]->GetGpa() << endl;
    } 

    for (int i = 0; i < MAX; i++)
       delete learners[i];   // engage virtual dest. sequence

    cout << endl;

    GraduateStudent gs1("Gabby", "Doone", 'A', "Miss", 3.9, "Creative Writing", "123GWU", "Prof. Page", "M.A.", "Gender Studies");
    GraduateStudent gs2("Renee", "Alexander", 'D', "Ms.", 3.9, "Quantum Mechanics", "453BU", "Prof. Richards", "PhD", "Dark Matter");
    gs1.EarnPhD();
    gs2.EarnPhD();
    gs1.Print();
    gs2.Print();

    return 0;
}

