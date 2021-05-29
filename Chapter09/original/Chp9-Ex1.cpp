// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate multiple inheritance.

#include <iostream>
#include <cstring>

using namespace std;

class Person
{
private: 
    char *firstName;
    char *lastName;
    char middleInitial;
    char *title;  // Mr., Ms., Mrs., Miss, Dr., etc.
    Person(const Person &);  // prohibit copies 
protected:
    void ModifyTitle(const char *);  
public:
    Person();   // default constructor
    Person(const char *, const char *, char, const char *);  
    virtual ~Person();  // destructor
    const char *GetFirstName() const { return firstName; }  
    const char *GetLastName() const { return lastName; }    
    const char *GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }
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

class BillableEntity
{
private:
    float invoiceAmt;
    BillableEntity(const BillableEntity &); // prohibit copies
public:
    BillableEntity() { invoiceAmt = 0.0; }
    BillableEntity(float amt) { invoiceAmt = amt; } 
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
    char *currentCourse;
    const char *studentId;  
    Student(const Student &);  // prohibit copies 
public:
    Student();  // default constructor
    Student(const char *, const char *, char, const char *,
           float, const char *, const char *, float); 
    virtual ~Student(); 
    void Print() const;
    void EarnPhD();  
    float GetGpa() const { return gpa; }
    const char *GetCurrentCourse() const { return currentCourse; }
    const char *GetStudentId() const { return studentId; }
    void SetCurrentCourse(const char *);
};

inline void Student::SetCurrentCourse(const char *c)
{
   delete currentCourse;   // delete existing course
   currentCourse = new char [strlen(c) + 1];
   strcpy(currentCourse, c); 
}

Student::Student() : studentId (0) // call default base  
{                                  // class constructors
   gpa = 0.0;
   currentCourse = 0;
}

// The member initialization list specifies which versions
// of each base class constructor should be utilized.
Student::Student(const char *fn, const char *ln, char mi, 
       const char *t, float avg, const char *course, 
       const char *id, float amt) :
       Person(fn, ln, mi, t), BillableEntity(amt)                   
{
   gpa = avg;
   currentCourse = new char [strlen(course) + 1];
   strcpy(currentCourse, course);
   char *temp = new char [strlen(id) + 1];
   strcpy (temp, id); 
   studentId = temp;
}

Student::~Student()
{
   delete currentCourse;
   delete (char *) studentId;
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
    Student s1("Gabby", "Doone", 'A', "Ms.", 3.9, "C++",
               "178GWU", tuition1); 
    Student s2("Zack", "Moon", 'R', "Dr.", 3.9, "C++",
               "272MIT", tuition2); 
    // public members of Person, BillableEntity, Student are
    // accessible from any scope, including main()
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

