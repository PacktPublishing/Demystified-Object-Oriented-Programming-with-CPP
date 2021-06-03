// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate Canonical Class form in a hierarchy of related classes 
// Explicit default constructor, copy constructor and overloaded assignment operators. And virtual destructor.
// Extended canonical class form: Adds move copy constructor and move assignment operator

#include <iostream>
#include <iomanip>
#include <cstring>    // Try not to worry -- We'll need one pointer data member to demonstrate a deep copy and assignment
                      // and a char * will provide a very easy to demonstrate data member for this purpose 
using std::cout;      // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::move;

constexpr int MAX = 5;

class Person
{
private: 
    string firstName;
    string lastName;
    char middleInitial;
    char *title;  // Mr., Ms., Mrs., Miss, Dr., etc. // we'll keep this data member as a char * to demonstrate deep copy/assignment
protected:
    void ModifyTitle(const string &); 
public:
    Person();   // default constructor
    Person(const string &, const string &, char, const char *);  
    Person(const Person &);  // copy constructor
    Person(Person &&);  // move copy constructor
    virtual ~Person();  // virtual destructor

    // inline function definitions
    const string &GetFirstName() const { return firstName; }  
    const string &GetLastName() const { return lastName; }    
    const char *GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }

    const string &SetLastName(const string &); 
    // Virtual functions will not be inlined since their 
    // method must be determined at run time using v-table.
    virtual void Print() const;
    virtual void IsA() const;  
    virtual void Greeting(const string &) const;

    Person &operator=(const Person &);  // overloaded assignment operator prototype
    Person &operator=(Person &&);  // move overloaded assignment operator prototype

};

Person::Person() : firstName(""), lastName(""), middleInitial('\0'), title(nullptr)
{
}

Person::Person(const string &fn, const string &ln, char mi, const char *t) : firstName(fn), lastName(ln), middleInitial(mi)
{
    // allocate memory for ptr data member, then fill with appropriate value
    title = new char [strlen(t) + 1];
    strcpy(title, t);
}

// copy constructor
Person::Person(const Person &p): firstName(p.firstName), lastName(p.lastName), middleInitial(p.middleInitial)
{
    cout << "Person copy constructor" << endl;
    // be sure to do a deep copy for the pointer data member -- allocate memory, then copy contents
    title = new char [strlen(p.title) + 1];
    strcpy(title, p.title);
}

// move copy constructor
// left hand object overtakes the dynamically allocated data members of right hand object
// Then null out right hand objects pointers (we've relinquished those members). Non-pointer data is just copied.
// Non-pointer data members (such as string or single char) are simply copied (string ensures a deep copy with =)
Person::Person(Person &&p)
{
    cout << "Person Move copy constructor" << endl;
    firstName = p.firstName;    
    p.firstName = "";     // set source object member to empty string
    lastName = p.lastName;
    p.lastName = ""; 
    middleInitial = p.middleInitial;
    p.middleInitial = '\0';   // set source object member to null character
    title = p.title;     // here, destinatation pointer takes over source pointer's memory
    p.title = nullptr;         // null out source pointer since memory should not be shared (it now belong to destination object)
}

Person::~Person()
{
    cout << "Person destructor" << endl;
    delete title;
}

void Person::ModifyTitle(const string &newTitle)
{
    delete title;  // delete old title
    title = new char[strlen(newTitle.c_str()) + 1];   // get the c string equivalent from the string
    strcpy(title, newTitle.c_str());

}

const string &Person::SetLastName(const string &ln)
{ 
    lastName = ln; 
    return lastName;
}

void Person::Print() const
{
    if (title)
       cout << title << " ";
    if (!firstName.empty())
       cout << firstName << " ";
    else
       cout << "No first name ";
    if (middleInitial != '\0')
       cout << middleInitial << ". ";
    if (!lastName.empty())
       cout << lastName << endl;
    else
       cout << "No last name" << endl;
}

void Person::IsA() const
{
    cout << "Person" << endl;
}

void Person::Greeting(const string &msg) const
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
      // delete memory for dynamically allocated data members
      delete title;   // or call ~Person(); -- unusual

      // re-allocate memory for pointer data members
      // copy each data member from source to destination object
      firstName = p.firstName;
      lastName = p.lastName;
      middleInitial = p.middleInitial;
      title = new char [strlen(p.title) + 1];   // mem allocation for ptr member
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
      // delete lhs original memory for pointer data members 
      delete title;    // or call ~Person() - unusual

      // Take over rhs object's data members (at least those which are pointers)
      // Once pointer data members are taken over by lhs, null out the rhs object's pointer to them
      // Non-pointer data members can be copied easily via assignment and then set to a zeroed or empty type value
      firstName = p.firstName;  // assignment between strings will be deep assignment
      p.firstName = "";         // set source data member to empty string to indicate non-use/existence
      lastName = p.lastName; 
      p.lastName = "";
      middleInitial = p.middleInitial;
      p.middleInitial = '\0';
      title = p.title;    // with ptr data member, this is a pointer assignemt - destination takes over source object's memory
      p.title = nullptr;
   }
   return *this;  // allow for cascaded assignments
}


class Student : public Person
{
private: 
    // data members
    float gpa;
    string currentCourse;
    const char *studentId;     // Again, we have one pointer data member to demonstrate deep copy / assignment
public:
    // member function prototypes
    Student();  // default constructor
    Student(const string &, const string &, char, const char *,
            float, const string &, const char *); 
    Student(const Student &);  // copy constructor
    Student(Student &&); // move copy constructor
    virtual ~Student();  // destructor
    void EarnPhD();  
    // inline function definitions
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const char *GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &); // prototype only
  
    // In the derived class, the keyword virtual is optional, 
    // but recommended for internal documentation
    virtual void Print() const override;
    virtual void IsA() const override;
    // note: we choose not to redefine Person::Greeting(const Student &) const
    Student &operator=(const Student &);  // overloaded assignment operator prototype
    Student &operator=(Student &&);  // overloaded move assignment operator prototype
};

inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
}

Student::Student() : gpa(0.0), currentCourse(""), studentId (0) 
{
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const char *t, float avg, const string &course, const char *id) : 
                 Person(fn, ln, mi, t), gpa(avg), currentCourse(course)
{
    char *temp = new char [strlen(id) + 1];
    strcpy (temp, id); 
    studentId = temp;
}

// Copy constructor definition
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse)
{
    cout << "Student copy constructor" << endl;
    // deep copy of pointer data member (use a temp since data is const and can't be directly copied into)
    char *temp = new char [strlen(s.studentId) + 1];
    strcpy (temp, s.studentId); 
    studentId = temp;
}
   
// move copy constructor
// left hand object overtakes the dynamically allocated data memberse of right hand object
// Then null out right hand objects pointer members (we've relinquished those members). Non-pointer data is just copied.
Student::Student(Student &&s) : Person(move(s))   // make sure we call base class Move copy constructor
{
    cout << "Student move copy constructor" << endl;
    gpa = s.gpa;   // copy then
    s.gpa = 0.0;   // zero out source object member
    currentCourse = s.currentCourse;
    s.currentCourse = ""; 
    // for ptr data member, destination data member takes over source data member's memory
    studentId = s.studentId;  // data is constant, pointer is not so assignment is ok
    s.studentId = nullptr;    // then null out source pointer data member 
}

// destructor definition
Student::~Student()
{
    cout << "Student destructor" << endl;
    delete (char *) studentId;    // fix cast
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
    if (!GetFirstName().empty())
        cout << GetFirstName() << " ";
    else
        cout << "No first name" << " ";
    if (GetMiddleInitial() != '\0')
        cout << GetMiddleInitial() << ". ";
    if (!GetLastName().empty())
        cout << GetLastName();
    if (studentId)
        cout << " with id: " << studentId;
    if (gpa != 0.0)
        cout << " GPA: " << setprecision(3) <<  " " << gpa;
    if (!currentCourse.empty())
        cout << " Course: " << currentCourse << endl;
    else
        cout << " No current course" << endl;
}

void Student::IsA() const
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

      // delete memory for existing destination data members that are pointers
      delete studentId;

      // for ptr data members, make a deep assignment -- reallocate memory then copy.
      // for non-ptr data members, an assignment is just fine
      gpa = s.gpa;           
      currentCourse = s.currentCourse;
      // deep copy of pointer data member (use a temp since data is const and can't be directly copied into)
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

      // delete lhs original data members that are pointers
      delete studentId;

      // Take over rhs object's data members (at least those which are pointers)
      // Once data members are taken over by lhs, null out the rhs object's pointer to them
      // for non-pointer members, an assignment is fine
      gpa = s.gpa;           
      s.gpa = 0.0;  // zero out source objects data member value 
      currentCourse = s.currentCourse;  // take over memory from pointer data members
      s.currentCourse = "";
      // for ptr data members, destination data member will take over source data member's memory
      studentId = s.studentId;  // this is a pointer assignment    
      s.studentId = nullptr;      // null out source object's data member (so they won't share the memory)
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

