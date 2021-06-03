// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate STL iterator 

#include <iostream>
#include <iomanip>
#include <cstring>
#include <list>
#include <iterator>

using namespace std;

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
    Person &operator=(const Person &); // overloaded assignment operator
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

// Copy constructor definition
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

// overloaded assignment operator
Person &Person::operator=(const Person &p)
{
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      delete firstName;  // or call ~Person();
      delete lastName;
      delete title;

      firstName = new char [strlen(p.firstName) + 1];
      strcpy(firstName, p.firstName);
      lastName = new char [strlen(p.lastName) + 1];
      strcpy(lastName, p.lastName);
      middleInitial = p.middleInitial;
      title = new char [strlen(p.title) + 1];
      strcpy(title, p.title);
   }
   return *this;  // allow for cascaded assignments
}

Person::~Person()
{
    // cout << "Person destructor " << this << endl;
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
    Student &operator=(const Student &); // overloaded assignment operator
    virtual ~Student();  // destructor
    void EarnPhD();  
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

// overloaded assignment operator
Student &Student::operator=(const Student &ps)
{
   // make sure we're not assigning an object to itself
   if (this != &ps)
   {
      Person::operator=(ps);

      delete currentCourse;  // or call ~Student();
      delete studentId;

      gpa = ps.gpa;
      currentCourse = new char [strlen(ps.currentCourse) + 1];
      strcpy(currentCourse, ps.currentCourse);
      char *temp = new char [strlen(ps.studentId) + 1];
      strcpy (temp, ps.studentId);
      studentId = temp;

   }
   return *this;  // allow for cascaded assignments
}

// destructor definition
Student::~Student()
{
    // cout << "Student destructor " << this << endl;
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

bool operator<(const Student &s1, const Student &s2)
{
    return (s1.GetGpa() < s2.GetGpa());
}

int main()
{
    list<Student> studentBody;
    Student s1("Jul", "Li", 'M', "Ms.", 3.8, "C++", "117PSU");

    // Add Students to the studentBody list. The list will make copies of the objects internally and will
    // properly clean up these objects when they are no longer members of the list.
    // You are responsible to delete and heap instances you provide to the list when you are done with them.
 
    // Add one student to the list.
    studentBody.push_back(s1);
    // Add three more Students to the list. These Students do not have local identifiers.
    // They are anonymous objects -- this is ok, they are directly added and copied in the container and 
    // the local copies in main will be propertly popped off the stack once added to the list.
    studentBody.push_back(Student("Hana", "Sato", 'U', "Dr.", 3.8, "C++", "178PSU")); 
    studentBody.push_back(Student("Sara", "Kato", 'B', "Dr.", 3.9, "C++", "272PSU")); 
    studentBody.push_back(Student("Giselle", "LeBrun", 'R', "Ms.", 3.4, "C++", "299TU")); 

    studentBody.sort();  // sort() will rely on operator< being defined for two Students
    // Create a list iterator and set to first item in the list
    list <Student>::iterator listIter = studentBody.begin();
    while (listIter != studentBody.end())
    {
        Student &temp = *listIter;
        temp.Print();
        listIter++;
    }

    return 0;
}

