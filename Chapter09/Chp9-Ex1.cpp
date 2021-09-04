// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate multiple inheritance.

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::string;
using std::to_string;

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
    Person(const Person &) = delete;  // prohibit copies 
    virtual ~Person();  // destructor
    const string &GetFirstName() const { return firstName; }  
    const string &GetLastName() const { return lastName; }    
    const string &GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }
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

// Simple destructor written ourselves, just so we can trace the destructor chain using cout statements
Person::~Person()
{
    cout << "Person destructor <" << firstName << " " << lastName << ">" << endl;
}

void Person::ModifyTitle(const string &newTitle)
{
    title = newTitle;
}

class BillableEntity
{
private:
    float invoiceAmt = 0.0;   // in-class initialization
public:
    BillableEntity()  = default;
    BillableEntity(float amt) : invoiceAmt(amt) { } 
    BillableEntity(const BillableEntity &) = delete; // prohibit copies
    virtual ~BillableEntity(); 
    void Pay(float amt) { invoiceAmt -= amt; }
    float GetBalance() const { return invoiceAmt; }
    void Balance();
};

// Simple destructor written ourselves, just so we can trace the destructor chain using cout statements
BillableEntity::~BillableEntity()
{
    cout << "BillableEntity destructor" << endl;
}

void BillableEntity::Balance()
{
    if (invoiceAmt)
       cout << "Owed amount: $ " << invoiceAmt << endl;
    else
       cout << "Credit: $ " << 0.0 - invoiceAmt << endl;
}

class Student: public Person, public BillableEntity
{
private: 
    float gpa = 0.0;   // in-class initialization
    string currentCourse;
    const string studentId;  
    static int numStudents;
public:
    Student();  // default constructor
    Student(const string &, const string &, char, const string &,
           float, const string &, const string &, float); 
    Student(const Student &) = delete;  // prohibit copies 
    ~Student() override; 
    void Print() const;
    void EarnPhD();  
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &);
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

// Due to non-specification in the member init list, this constructor calls the default base class constructors
Student::Student() : studentId(to_string(numStudents + 100) + "Id")
{
   // Note: since studentId is const, we need to set it at construction. We're doing so in member init list with
   // a unique id (based upon numStudents counter + 100), concatenated with the string "Id" .
   // Remember, string member currentCourse will be default constructed with an empty string - it is a member object
   // Also, remember to dynamically allocate memory for any pointer data members here (not needed in this example)
   numStudents++;
}

// The member initialization list specifies which versions of each base class constructor should be utilized.
Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, 
                 const string &course, const string &id, float amt) :
                 Person(fn, ln, mi, t), BillableEntity(amt),
                 gpa(avg), currentCourse(course), studentId(id) 
{
   numStudents++;
}

// Simple destructor written ourselves, just so we can trace the destructor chain using cout statements
Student::~Student()
{
   numStudents--;
   cout << "Student destructor <" << GetFirstName() << " " << GetLastName() << ">" << endl;
}

void Student::Print() const
{
    cout << GetTitle() << " " << GetFirstName() << " ";
    cout << GetMiddleInitial() << ". " << GetLastName();
    cout << " with id: " << studentId << " has a gpa of: ";
    cout << " " << gpa << " and course: " << currentCourse;
    cout << " with balance: $" << GetBalance() << endl;
}

void Student::EarnPhD() 
{  
    ModifyTitle("Dr."); 
}

int main()
{
    float tuition1 = 1000.00, tuition2 = 2000.00;
    Student s1("Gabby", "Doone", 'A', "Ms.", 3.9, "C++", "178GWU", tuition1); 
    Student s2("Zack", "Moon", 'R', "Dr.", 3.9, "C++", "272MIT", tuition2); 
    // public members of Person, BillableEntity, Student are accessible from any scope, including main()
    s1.Print();
    s2.Print();
    cout << s1.GetFirstName() << " paid $500.00" << endl;
    s1.Pay(500.00);
    cout << s2.GetFirstName() << " paid $750.00" << endl;
    s2.Pay(750.00);
    cout << s1.GetFirstName() << ": ";
    s1.Balance();
    cout << s2.GetFirstName() << ": ";
    s2.Balance();
    return 0;
}

