// (c) Copyright Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate abstract classes, pure virtual functions
// and storing related derived class types using sets of pointers which are the abstract class type. 

#include <iostream>
#include <iomanip>

using std::cout;     // preferred to:  using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::to_string;

constexpr int MAX = 5;

// An abstract class is one which collects common traits of derived classes,
// yet is does not itself represent a tangible entity, or an object which 
// should be instantiated.  In order to specify a class to be abstract, it 
// must contain at least one pure virtual function.  A derived class which
// does not redefine all pure virtual functions in its base class is also
// considered an abstract class (and can't be instantiated). 

class LifeForm   // abstract class definition
{
private:
   int lifeExpectancy = 0;  // in-class initialization
public:
   LifeForm() = default;    // use default ctor and in-class initialization
   LifeForm(int life) : lifeExpectancy(life) { }
   LifeForm(const LifeForm &) = default;
   // If we wanted to write the copy constructor, this is what it would look like:
   // LifeForm(const LifeForm &form) : lifeExpectancy(form.lifeExpectancy) { }   OR
   // LifeForm(const LifeForm &form) { lifeExpectancy = form.lifeExpectancy; }
   virtual ~LifeForm() = default;      // virtual destructor
   int GetLifeExpectancy() const { return lifeExpectancy; }
   virtual void Print() const = 0;   // pure virtual functions 
   virtual string IsA() const = 0;   
   virtual string Speak() const = 0;
};

class Cat: public LifeForm
{
private:
   int numberLivesLeft = 9;   // in-class initialization
   string name;
public:
   Cat() : LifeForm(15) { }  // remember, numberLivesLeft is set with in-class init and name will be an empty string
   Cat(int lives) : LifeForm(15), numberLivesLeft(lives) {  }
   Cat(const string &);
   ~Cat() override = default;    // virtual destructor
   const string &GetName() const { return name; }
   int GetNumberLivesLeft() const { return numberLivesLeft; }
   void Print() const override;   // redefine pure virtual functions
   string IsA() const override { return "Cat"; }
   string Speak() const override { return "Meow!"; }
};

Cat::Cat(const string &n) : LifeForm(15), name(n)  // numLivesLeft will be set to 9 with in-class init
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
   char middleInitial = '\0';  // in-class initialization
   string title;  // Mr., Ms., Mrs., Miss, Dr., etc.
protected:
   void ModifyTitle(const string &);  
public:
   Person();   // programmer supplied default constructor
   Person(const string &, const string &, char, const string &);  
   Person(const Person &) = default;  // copy constructor
   ~Person() override = default;  // destructor
   const string &GetFirstName() const { return firstName; }  
   const string &GetLastName() const { return lastName; }    
   const string &GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
   void Print() const override;  // redefine pure virtual functions
   string IsA() const override;   
   string Speak() const override;
};


// With in-class initialization, we don't need to set middleInitial.  
// Remember, string members are automatically initialized to empty with the default string constructor
// However, we will select the LifeForm(int) constructor in the member init list to allow us to pass a lifexpectancy of 80
Person::Person() : LifeForm(80)
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) : 
               LifeForm(80), firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

// We don't need to write the copy constructor ourselves (there are no ptr data members in class).
// If we did choose to do so, this is how it would look:
/*
Person::Person(const Person &p) : LifeForm(p), firstName(p.firstName), lastName(p.lastName), 
                                               middleInitial(p.middleInitial), title(p.title)
{
}
*/

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
   float gpa = 0.0;    // in-class initialization
   string currentCourse;
   const string studentId;  
   static int numStudents;
public:
   Student();  // default constructor
   Student(const string &, const string &, char, const string &, float, const string &, const string &); 
   Student(const Student &);  // copy constructor
   ~Student() override;  // destructor
   void EarnPhD();  
   float GetGpa() const { return gpa; }
   const string &GetCurrentCourse() const { return currentCourse; }
   const string &GetStudentId() const { return studentId; }
   void SetCurrentCourse(const string &);
   void Print() const final override; // redefine not all virtual functions (and mark Print as the final override)
   string IsA() const override;
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
   numStudents++;
}



// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t,
                 float avg, const string &course, const string &id) : 
                 Person(fn, ln, mi, t), gpa(avg), currentCourse(course), studentId(id)
{
   numStudents++;
}

// Copy constructor definition
Student::Student(const Student &s) : Person(s), gpa(s.gpa), currentCourse(s.currentCourse), studentId(s.studentId)
{
   numStudents++;
}
   
// destructor definition. We have additional work to do so we can't just accept the default implementation
Student::~Student()
{
   numStudents--;
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
   cout << setprecision(3) <<  " " << gpa << " enrolled in: ";
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

