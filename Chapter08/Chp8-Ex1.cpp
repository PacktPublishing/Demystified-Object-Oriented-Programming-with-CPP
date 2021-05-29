// (c) Copyright Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate abstract classes, pure virtual functions
// and storing related derived class types using sets of pointers which are the abstract class type. 

#include <iostream>
#include <iomanip>

using std::cout;     // preferred to:  using namespace std;
using std::endl;
using std::setprecision;
using std::string;

const int MAX = 5;

// An abstract class is one which collects common traits of derived classes,
// yet is does not itself represent a tangible entity, or an object which 
// should be instantiated.  In order to specify a class to be abstract, it 
// must contain at least one pure virtual function.  A derived class which
// does not redefine all pure virtual functions in its base class is also
// considered an abstract class (and can't be instantiated). 

class LifeForm   // abstract class definition
{
private:
   int lifeExpectancy;
public:
   LifeForm() { lifeExpectancy = 0; }
   LifeForm(int life) { lifeExpectancy = life; }
   LifeForm(const LifeForm &form) 
       { lifeExpectancy = form.lifeExpectancy; }
   virtual ~LifeForm() { }      // virtual destructor
   int GetLifeExpectancy() const { return lifeExpectancy; }
   virtual void Print() const = 0;   // pure virtual functions 
   virtual string IsA() const = 0;   
   virtual string Speak() const = 0;
};

class Cat: public LifeForm
{
private:
   int numberLivesLeft;
   string name;
public:
   Cat() : LifeForm(15), numberLivesLeft(9), name("") {  }
   Cat(int lives) : LifeForm(15), numberLivesLeft(lives), name("") {  }
   Cat(const string &);
   virtual ~Cat() { }   // virtual destructor
   const string &GetName() const { return name; }
   int GetNumberLivesLeft() const { return numberLivesLeft; }
   virtual void Print() const override;   // redefine pure virtual functions
   virtual string IsA() const override { return "Cat"; }
   virtual string Speak() const override { return "Meow!"; }
};

Cat::Cat(const string &n) : LifeForm(15), numberLivesLeft(9), name(n)
{
}

void Cat::Print() const
{
   cout << "\t" << name << " has " << numberLivesLeft; 
   cout << " lives left" << endl;
}

class Person : public LifeForm
{
private: 
   // data members
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
   virtual ~Person();  // destructor
   const string &GetFirstName() const { return firstName; }  
   const string &GetLastName() const { return lastName; }    
   const string &GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
   virtual void Print() const override;  // redefine pure virtual functions
   virtual string IsA() const override;   
   virtual string Speak() const override;
};

Person::Person() : LifeForm(80), firstName(""), lastName(""), middleInitial('\0'), title("")
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : 
               LifeForm(80), firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person::Person(const Person &p) : LifeForm(p), firstName(p.firstName), lastName(p.lastName), 
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
   cout << "\t" << title << " " << firstName << " ";
   cout << middleInitial << ". " << lastName << endl;
}

string Person::IsA() const
{
   return "Person";
}

string Person::Speak() const
{
   return "Hello!";
}   

class Student : public Person
{
private: 
   // data members
   float gpa;
   string currentCourse;
   const string studentId;  
public:
   Student();  // default constructor
   Student(const string &, const string &, char, const string &,
           float, const string &, const string &); 
   Student(const Student &);  // copy constructor
   virtual ~Student();  // destructor
   void EarnPhD();  
   float GetGpa() const { return gpa; }
   const string &GetCurrentCourse() const { return currentCourse; }
   const string &GetStudentId() const { return studentId; }
   void SetCurrentCourse(const string &);
   virtual void Print() const final override; // redefine not all virtual functions (and mark Print as the final override)
   virtual string IsA() const override;
};

inline void Student::SetCurrentCourse(const string &c)
{
   currentCourse = c;
}

Student::Student() : gpa(0.0), currentCourse(""), studentId ("")
{
   // It would be a better idea to initialize studentId to a random id (since it is const and cannot be later reset)
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t,
                 float avg, const string &course, const string &id) : 
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

void Student::EarnPhD()
{
   ModifyTitle("Dr.");  
}

void Student::Print() const
{
   cout << "\t" << GetTitle() << " " << GetFirstName() << " ";
   cout << GetMiddleInitial() << ". " << GetLastName();
   cout << " id: " << studentId << "\n\twith gpa: ";   // tab \t followed by word 'with' (no space purposefully)
   cout << setprecision(2) <<  " " << gpa << " enrolled in: ";
   cout << currentCourse << endl;
}

string Student::IsA() const
{
   return "Student";
}

int main()
{
   // Notice that we are creating an array of POINTERS to
   // LifeForms.  Since LifeForm cannot be instantiated, 
   // we could not create an array of LifeForm (s).
   LifeForm *entity[MAX] = {nullptr, nullptr, nullptr, nullptr, nullptr};
  
   entity[0] = new Person("Joy", "Lin", 'M', "Ms.");
   entity[1] = new Student("Renee", "Alexander", 'Z', "Dr.", 3.95, "C++", "21-MIT"); 
   entity[2] = new Student("Gabby", "Doone", 'A', "Ms.", 3.95, "C++", "18-GWU"); 
   entity[3] = new Cat("Katje"); 
   entity[4] = new Person("Giselle", "LeBrun", 'R', "Miss");

   for (int i = 0; i < MAX; i++)
   {
      cout << entity[i]->Speak();
      cout << " I am a " << entity[i]->IsA() << endl;
      entity[i]->Print();
      cout << "\tHas a life expectancy of: ";
      cout << entity[i]->GetLifeExpectancy();
      cout << "\n";
   } 

   for (int i = 0; i < MAX; i++)
   {
      delete entity[i];
      entity[i] = nullptr;   // ensure deleted pointer isn't used
   }

   return 0;
}

