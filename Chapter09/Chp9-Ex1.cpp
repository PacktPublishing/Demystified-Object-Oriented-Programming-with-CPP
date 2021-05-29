// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate multiple inheritance.

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::string;

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
    Person(const Person &) = delete;  // prohibit copies 
    virtual ~Person();  // destructor
    const string &GetFirstName() const { return firstName; }  
    const string &GetLastName() const { return lastName; }    
    const string &GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }
};


Person::Person() : firstName(""), lastName(""), middleInitial('\0'), title("")
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : 
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person::~Person()
{
}

void Person::ModifyTitle(const string &newTitle)
{
    title = newTitle;
}

class BillableEntity
{
private:
    float invoiceAmt;
public:
    BillableEntity() { invoiceAmt = 0.0; }
    BillableEntity(float amt) { invoiceAmt = amt; } 
    BillableEntity(const BillableEntity &) = delete; // prohibit copies
    virtual ~BillableEntity() { }
    void Pay(float amt) { invoiceAmt -= amt; }
    float GetBalance() const { return invoiceAmt; }
    void Balance();
};

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
    float gpa;
    string currentCourse;
    const string studentId;  
public:
    Student();  // default constructor
    Student(const string &, const string &, char, const string &,
           float, const string &, const string &, float); 
    Student(const Student &) = delete;  // prohibit copies 
    virtual ~Student(); 
    void Print() const;
    void EarnPhD();  
    float GetGpa() const { return gpa; }
    const string &GetCurrentCourse() const { return currentCourse; }
    const string &GetStudentId() const { return studentId; }
    void SetCurrentCourse(const string &);
};

inline void Student::SetCurrentCourse(const string &c)
{
    currentCourse = c;
}

// Due to non-specification, this constructor calls the default base class constructors
Student::Student() : gpa(0.0), currentCourse(""), studentId ("") 
{ 
}

// The member initialization list specifies which versions of each base class constructor should be utilized.
Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, 
                 const string &course, const string &id, float amt) :
                 Person(fn, ln, mi, t), BillableEntity(amt),
                 gpa(avg), currentCourse(course), studentId(id) 
{
}

Student::~Student()
{
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

