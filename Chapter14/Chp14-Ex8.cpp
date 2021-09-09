// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate STL map with a functor.

#include <iostream>
#include <iomanip>
#include <map>

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;
using std::map;
using std::pair;

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
    Person &operator=(const Person &); // overloaded assignment operator
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

//  Remember, we're using default versions of default constructor, copy constructor and destructor
//  so the code for these methods is not included below by us

Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      // delete any previously dynamically allocated data members here from the destination object
      // or call ~Person() to release this memory -- unconventional

      // Also, remember to reallocate memory for any data members that are pointers.

      // copy from source to destination object each data member
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = p.title;
   }
   return *this;  // allow for cascaded assignments
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


class Student : public Person
{
private: 
    float gpa = 0.0;
    string currentCourse;
    string studentId;      // decided to make studentId not const (a design decision that makes op= more productive, etc.) 
    static int numStudents;
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, const string &); 
    Student(const Student &);  // copy constructor
    Student &operator=(const Student &); // overloaded assignment operator
    ~Student() override;  // virtual destructor
    void EarnPhD();  
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only
  
    // In the derived class, the keyword virtual is optional for overridden (polymorphic) methods, as is the keyword "override"
    // Currently, "override" is recommended for internal documentation, however "virtual" is not recommended
    void Print() const override;
    void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const string &); const

    static int GetNumberStudents() { return numStudents; }
};


int Student::numStudents = 0;  // definition of static data member


inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
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
}

// overloaded assignment operator
Student &Student::operator=(const Student &s)
{
   // make sure we're not assigning an object to itself
   if (this != &s)
   {
      Person::operator=(s);

      // delete any dynamically allocated data members in destination Student (or call ~Student() - unconventional)

      // remember to allocate any memory in destination for copies of source members

      // copy data members from source to desination object
      gpa = s.gpa;
      currentCourse = s.currentCourse;
      studentId = s.studentId;

   }
   return *this;  // allow for cascaded assignments
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


bool operator==(const Student &s1, const Student &s2)
{
    return (s1.GetGpa() == s2.GetGpa());
}

struct comparison   // This struct represents a ‘functor’
{                   // that is, a ‘function object’
    bool operator() (string key1, string key2) const
    {   
        int ans = key1.compare(key2);
        if (ans >= 0) 
            return true;   // return true if greater than or =
        else 
            return false;  // return false if they are equal or less than
    }
    comparison() { }
    ~comparison() { }
};


int main()
{
    Student s1("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU"); 
    Student s2("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU"); 
    Student s3("Jill", "Long", 'R', "Dr.", 3.7, "C++", "234PSU"); 

    // Now, map is maintained in sorted order per comparison functor using operator()
    map<string, Student, comparison> studentBody;
    map<string, Student, comparison>::iterator mapIter;

    // create three pairings of ids to Students
    pair<string, Student> studentPair1(s1.GetStudentId(), s1); 
    pair<string, Student> studentPair2(s2.GetStudentId(), s2); 
    pair<string, Student> studentPair3(s3.GetStudentId(), s3); 

    studentBody.insert(studentPair1);   // insert a pair instance
    studentBody.insert(studentPair2);
    studentBody.insert(studentPair3);
    
    mapIter = studentBody.begin();
    while (mapIter != studentBody.end())
    {
        pair<string, Student> temp = *mapIter;
        Student &tempS = temp.second;  // get second item in the 'pair' (a Student)
        cout << temp.first << " " << temp.second.GetFirstName();    // access using mapIter
        cout << " " << tempS.GetLastName() << endl;  // or access using temp Student
        mapIter++;
    } 

    return 0;
}
