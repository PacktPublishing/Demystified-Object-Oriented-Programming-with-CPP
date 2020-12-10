// (c) Copyright Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate abstract classes, pure virtual functions
// and storing related derived class types using sets of pointers which are the abstract class type. 

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
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
   virtual const char *IsA() = 0;   
   virtual const char *Speak() = 0;
};

class Cat: public LifeForm
{
private:
   int numberLivesLeft;
   char *name;
public:
   Cat() : LifeForm(15) { numberLivesLeft = 9; name = 0; }
   Cat(int lives) : LifeForm(15) { numberLivesLeft = lives; }
   Cat(const char *n);
   virtual ~Cat() { delete name; }   // virtual destructor
   const char *GetName() const { return name; }
   int GetNumberLivesLeft() const { return numberLivesLeft; }
   virtual void Print() const override;   // redefine pure virtual functions
   virtual const char *IsA() override { return "Cat"; }
   virtual const char *Speak() override { return "Meow!"; }
};

Cat::Cat(const char *n) : LifeForm(15)
{
   name = new char [strlen(n) + 1];
   strcpy(name, n);
   numberLivesLeft = 9;
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
   virtual ~Person();  // destructor
   const char *GetFirstName() const { return firstName; }  
   const char *GetLastName() const { return lastName; }    
   const char *GetTitle() const { return title; } 
   char GetMiddleInitial() const { return middleInitial; }
   virtual void Print() const override;  // redefine pure virtual functions
   virtual const char *IsA() override;   
   virtual const char *Speak() override;
};

Person::Person() : LifeForm(80)
{
   firstName = lastName = 0;  // NULL pointer
   middleInitial = '\0';
   title = 0;
}

Person::Person(const char *fn, const char *ln, char mi, const char *t) : 
               LifeForm(80)
{
   firstName = new char [strlen(fn) + 1];
   strcpy(firstName, fn);
   lastName = new char [strlen(ln) + 1];
   strcpy(lastName, ln);
   middleInitial = mi;
   title = new char [strlen(t) + 1];
   strcpy(title, t);
}

Person::Person(const Person &pers) : LifeForm(pers)
{
   firstName = new char [strlen(pers.firstName) + 1];
   strcpy(firstName, pers.firstName);
   lastName = new char [strlen(pers.lastName) + 1];
   strcpy(lastName, pers.lastName);
   middleInitial = pers.middleInitial;
   title = new char [strlen(pers.title) + 1];
   strcpy(title, pers.title);
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

void Person::Print() const
{
   cout << "\t" << title << " " << firstName << " ";
   cout << middleInitial << ". " << lastName << endl;
}

const char *Person::IsA()
{
   return "Person";
}

const char *Person::Speak()
{
   return "Hello!";
}   

class Student : public Person
{
private: 
   // data members
   float gpa;
   char *currentCourse;
   const char *studentId;  
public:
   Student();  // default constructor
   Student(const char *, const char *, char, const char *,
           float, const char *, const char *); 
   Student(const Student &);  // copy constructor
   virtual ~Student();  // destructor
   void EarnPhD();  
   float GetGpa() const { return gpa; }
   const char *GetCurrentCourse() const { return currentCourse; }
   const char *GetStudentId() const { return studentId; }
   void SetCurrentCourse(const char *);
   virtual void Print() const override; // redefine not all virtual functions
   virtual const char *IsA() override;
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
Student::Student(const char *fn, const char *ln, char mi, const char *t,
                 float avg, const char *course, const char *id) : 
                 Person(fn, ln, mi, t)
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
   
// destructor definition
Student::~Student()
{
   delete currentCourse;
   delete (char *) studentId;
}

void Student::EarnPhD()
{
   ModifyTitle("Dr.");  
}

void Student::Print() const
{
   cout << "\t" << GetTitle() << " " << GetFirstName() << " ";
   cout << GetMiddleInitial() << ". " << GetLastName();
   cout << " with id: " << studentId << " has a gpa of: ";
   cout << setprecision(2) <<  " " << gpa << " enrolled in: ";
   cout << currentCourse << endl;
}

const char *Student::IsA()
{
   return "Student";
}

int main()
{
   // Notice that we are creating an array of POINTERS to
   // LifeForms.  Since LifeForm cannot be instantiated, 
   // we could not create an array of LifeForm (s).
   LifeForm *entity[MAX];
  
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
      delete entity[i];

   return 0;
}

