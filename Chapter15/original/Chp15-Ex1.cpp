// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate Canonical Class form in a hierarchy of related classes 
// Explicit default constructor, copy constructor and overloaded assignment operators. And virtual destructor.
// Extended canonical class form: Adds move copy constructor and move assignment operator

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX = 5;

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
    Person(Person &&);  // move copy constructor
    virtual ~Person();  // virtual destructor

    // inline function definitions
    const char *GetFirstName() const { return firstName; }  
    const char *GetLastName() const { return lastName; }    
    const char *GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }

    const char *SetLastName(const char *ln); 
    // Virtual functions will not be inlined since their 
    // method must be determined at run time using v-table.
    virtual void Print() const;
    virtual void IsA();  
    virtual void Greeting(const char *);

    Person &operator=(const Person &);  // overloaded assignment operator prototype
    Person &operator=(Person &&);  // move overloaded assignment operator prototype

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

// copy constructor
Person::Person(const Person &pers)
{
    cout << "Person copy constructor" << endl;
    firstName = new char [strlen(pers.firstName) + 1];
    strcpy(firstName, pers.firstName);
    lastName = new char [strlen(pers.lastName) + 1];
    strcpy(lastName, pers.lastName);
    middleInitial = pers.middleInitial;
    title = new char [strlen(pers.title) + 1];
    strcpy(title, pers.title);
}

// move copy constructor
// left hand object overtakes the dynamically allocated data memberse of right hand object
// Then null out right hand objects pointers (we've relinquished those members). Non-pointer data is just copied.
Person::Person(Person &&pers)
{
    cout << "Person Move copy constructor" << endl;
    firstName = pers.firstName;
    pers.firstName = 0; 
    lastName = pers.lastName;
    pers.lastName = 0; 
    middleInitial = pers.middleInitial;
    pers.middleInitial = '\0';
    title = pers.title; 
    pers.title = 0;
}

Person::~Person()
{
    cout << "Person destructor" << endl;
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

const char *Person::SetLastName(const char *ln)
{ 
    delete lastName; 
    lastName = new char[strlen(ln) + 1]; 
    strcpy(lastName, ln); 
    return lastName;
}

void Person::Print() const
{
    if (title)
       cout << title << " ";
    if (firstName)
       cout << firstName << " ";
    else
       cout << "No first name ";
    if (middleInitial != '\0')
       cout << middleInitial << ". ";
    if (lastName)
       cout << lastName << endl;
    else
       cout << "No last name" << endl;
}

void Person::IsA()
{
    cout << "Person" << endl;
}

void Person::Greeting(const char *msg)
{
    cout << msg << endl;
}

// overloaded assignment operator
Person &Person::operator=(const Person &p)
{
   cout << "Person assignment operator" << endl;
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

// overloaded move assignment operator
Person &Person::operator=(Person &&p)
{
   cout << "Person move assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &p)
   {
      // delete lhs original data
      delete firstName;  // or call ~Person();
      delete lastName;
      delete title;

      // Take over rhs object's data members (at least those which are pointers)
      // Once data members are taken over by lhs, null out the rhs object's pointer to them
      firstName = p.firstName; 
      p.firstName = 0;
      lastName = p.lastName; 
      p.lastName = 0;
      middleInitial = p.middleInitial;
      p.middleInitial = '\0';
      title = p.title; 
      p.title = 0;
   }
   return *this;  // allow for cascaded assignments
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
    Student(Student &&); // move copy constructor
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
    Student &operator=(const Student &);  // overloaded assignment operator prototype
    Student &operator=(Student &&);  // overloaded move assignment operator prototype
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
    cout << "Student copy constructor" << endl;
    gpa = ps.gpa;
    currentCourse = new char [strlen(ps.currentCourse) + 1];
    strcpy(currentCourse, ps.currentCourse);
    char *temp = new char [strlen(ps.studentId) + 1];
    strcpy (temp, ps.studentId); 
    studentId = temp;
}
   
// move copy constructor
// left hand object overtakes the dynamically allocated data memberse of right hand object
// Then null out right hand objects pointers (we've relinquished those members). Non-pointer data is just copied.
Student::Student(Student &&ps) : Person(move(ps))   // make sure we call base class Move copy constructor
{
    cout << "Student move copy constructor" << endl;
    gpa = ps.gpa;
    ps.gpa = 0.0;
    currentCourse = ps.currentCourse;
    ps.currentCourse = 0; 
    studentId = ps.studentId;  // data is constant, pointer is not so assignment is ok
    ps.studentId = 0;
}

// destructor definition
Student::~Student()
{
    cout << "Student destructor" << endl;
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
    if (GetTitle())
        cout << GetTitle() << " ";
    if (GetFirstName())
        cout << GetFirstName() << " ";
    else
        cout << "No first name" << " ";
    if (GetMiddleInitial() != '\0')
        cout << GetMiddleInitial() << ". ";
    if (GetLastName())
        cout << GetLastName();
    if (studentId)
        cout << " with id: " << studentId;
    if (gpa != 0.0)
        cout << " GPA: " << setprecision(3) <<  " " << gpa;
    if (currentCourse)
        cout << " Course: " << currentCourse << endl;
    else
        cout << " No current course" << endl;
}

void Student::IsA()
{
    cout << "Student" << endl;
}

// overloaded assignment operator
Student &Student::operator=(const Student &s)
{
   cout << "Student assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &s)
   {
      Person::operator=(s);  // call base class operator= for help

      delete currentCourse;  // delete existing data members
      delete studentId;

      gpa = s.gpa;           // make deep assignment of data members
      currentCourse = new char [strlen(s.currentCourse) + 1];
      strcpy(currentCourse, s.currentCourse);
      char *temp = new char [strlen(s.studentId) + 1];
      strcpy (temp, s.studentId); 
      studentId = temp;
   }
   return *this;  // allow for cascaded assignments
}

// overloaded move assignment operator
Student &Student::operator=(Student &&s)
{
   cout << "Student Move assignment operator" << endl;
   // make sure we're not assigning an object to itself
   if (this != &s)
   {
      Person::operator=(move(s));  // call base class operator= for help

      // delete lhs original data
      delete currentCourse;  // delete existing data members
      delete studentId;

      // Take over rhs object's data members (at least those which are pointers)
      // Once data members are taken over by lhs, null out the rhs object's pointer to them
      gpa = s.gpa;           
      s.gpa = 0.0;
      currentCourse = s.currentCourse;  // take over memory from pointer data members
      s.currentCourse = 0;
      studentId = s.studentId; 
      s.studentId = 0;
   }
   return *this;  // allow for cascaded assignments
}

int main()
{
    // Show default, copy, assignment operator, and virtual destructor. 
    // Also show move copy and move assignment.

    // Simple cases of move, without inheritance
    Person p1("Alexa", "Gutierrez", 'R', "Ms.");
    p1.Print();
    Person p2(move(p1));  // move copy constructor
    p1.Print();
    p2.Print();
    Person p3 = move(p2); // this is an initialization (not assignment) and calls move copy constructor
    p2.Print();
    p3.Print();

    Person p5("Xander", "LeBrun", 'R', "Dr."); 
    p5.Print();
    p5 = move(p3);  // move assignment, in place of original instance 
    p3.Print();
    p5.Print();

    // More complex cases, demonstrates uses of canonical form with inherited classes
    Student s0;  // default constructor
    Student s1("Jules", "Martinez", 'M', "Ms.", 3.2, "C++", "3562UD");  // alternate constructor
    Person *p4 = new Student("George", "Valente", 'Q', "Mr.", 3.5, "Adv. C++", "1178UD");   // note: upcast to a base type

    cout << "Copy constructor" << endl;
    Student s2(s1);  // copy constructor
    s1.Print();
    s2.Print();
    s1.SetLastName("Martin");
    s2.SetLastName("Martine");
    s1.Print();
    s2.Print();

    cout << "Move copy constructor" << endl;
    Student s3(move(s1));   // Move constructor
    s3.Print();
    s1.Print();
    s3.SetLastName("Jonez");
    s1.SetLastName("Jones");
    s3.Print();
    s1.Print();

    cout << "Overloaded assignment operator" << endl;
    s0 = s3;  // overloaded assignment operator
    s0.Print();
    s3.Print();
    s0.SetLastName("Smith");
    s3.SetLastName("Smythe");
    s0.Print();
    s3.Print();

    cout << "Overloaded move assignment operator" << endl;
    s2 = move(s3);
    s2.Print();
    s3.Print();
    s2.SetLastName("Green");
    s3.SetLastName("Greene");
    s2.Print();
    s3.Print();

    cout << "Destructor sequences" << endl;
    delete p4;  // This truly points to a Student, so we'll see virtual destruction sequence in action

    return 0;
}

