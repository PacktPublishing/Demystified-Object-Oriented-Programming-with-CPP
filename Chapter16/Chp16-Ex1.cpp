// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To illustrate the Observer Pattern 

#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>

using std::cout;   // prefered to: using namespace std;
using std::endl;
using std::setprecision;
using std::string;
using std::list;

constexpr int MAXCOURSES = 5, MAXSTUDENTS = 5;

class Subject;  // forward declarations
class Student;

class Observer
{
private:
    int observerState;
protected:
    Observer() { observerState = 0; }
    Observer(int s) { observerState = s; }
    void SetState(int s) { observerState = s; }
public: 
    int GetState() const { return observerState; }
    virtual ~Observer() {}
    virtual void Update() = 0;
};

class Subject
{
private:
    list<class Observer *> observers;  // List of Observers will be Students on wait-list
    int numObservers;
    int subjectState;
    list<Observer *>::iterator newIter;
protected:
    Subject() { subjectState = 0; numObservers = 0; }
    Subject(int s) { subjectState = s; numObservers = 0; }
    void SetState(int s) { subjectState = s; }
public:
    int GetState() const { return subjectState; }
    int GetNumObservers() const { return numObservers; }
    virtual ~Subject() {}
    virtual void Register(Observer *);
    virtual void Release(Observer *);
    virtual void Notify();
};

void Subject::Register(Observer *ob)
{
    observers.push_back(ob);
    numObservers++;
}

void Subject::Release(Observer *ob)
{
    bool found;
    for (list<Observer *>::iterator iter = observers.begin(); iter != observers.end() && !found; iter++)
    {
        Observer *temp = *iter;
        if (temp == ob)    // if we found observer which we seek
        {
            // erase element, iterator is now corrupt; save off good iterator, we'll need it later
            newIter = observers.erase(iter);  
            found = true;  // no need to loop after we've found our desired observer
            numObservers--;
        }
    }
}

void Subject::Notify()
{
    for (list<Observer *>::iterator iter = observers.begin(); iter != observers.end(); iter++)
    {
        // cout << " list size: " << observers.size() << endl;
        Observer *temp = *iter;
        temp->Update();      // same as (*iter)->Update();
        // State 1 means we added course, got off waitlist (so waitlist had a removal), so update the iterator
        if (temp->GetState() == 1)  
            iter = newIter;  // update the iterator, as once we do an erase(), our iterator is corrupted
    }
    if (observers.size() != 0)
    {
        Observer *last = *newIter;   // Update last item on waitlist
        last->Update();
    }
}


class Course: public Subject   // over-simplified Course class
{                              // inherits observer list (from Subject) which will represent Students on wait-list
private:
    string title;
    int number;
    Student *students[MAXSTUDENTS];  // List of Students enrolled in Course
    int totalStudents;
public:
    Course(const string &title, int num): number(num), totalStudents(0)
    {
        this->title = title;   // or use different parameter name and set in member init list
        for (int i = 0; i < MAXSTUDENTS; i++)
            students[i] = nullptr;
    }
    virtual ~Course() { }  // More work needed - don't forget to remove Students from Course!
    int GetCourseNum() const { return number; }
    const string &GetTitle() const { return title; }
    bool AddStudent(Student *);
    void Open() { SetState(1); Notify(); } // Once a course is Open for enrollment, we Notify() the Observers (Students) 
    void PrintStudents() const;
}; 

bool Course::AddStudent(Student *s) 
{   
    // should also check to ensure Student isn't already added to Course
    if (totalStudents < MAXSTUDENTS)  // make sure Course is not full
    {
        students[totalStudents++] = s; 
        return true;
    }
    else 
        return false;
} 

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
    Person(const Person &);  // copy constructor
    virtual ~Person();  // virtual destructor

    const string &GetFirstName() const { return firstName; }  
    const string &GetLastName() const { return lastName; }    
    const string &GetTitle() const { return title; } 
    char GetMiddleInitial() const { return middleInitial; }

    virtual void Print() const;
    virtual void IsA() const;  
    virtual void Greeting(const string &) const;
};

Person::Person() : firstName(""), lastName(""), middleInitial('\0'), title("")
{
}

Person::Person(const string &fn, const string &ln, char mi, const string &t) :
               firstName(fn), lastName(ln), middleInitial(mi), title(t)
{
}

Person::Person(const Person &p) : firstName(p.firstName), lastName(p.lastName),
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

class Student : public Person, public Observer
{
private: 
    float gpa;
    const string studentId;  
    int currentNumCourses;
    Course *courses[MAXCOURSES];
    Course *waitList;  // Course we'd like to take - we're on the waitlist -- this is our Subject in specialized form
public:
    Student();  // default constructor
    Student(const string &, const string &, char, const string &, float, const string &, Course *); 
    Student(const string &, const string &, char, const string &, float, const string &); 
    Student(const Student &) = delete;  // copy constructor is now Disallowed 
    virtual ~Student();  // destructor
    void EarnPhD();  

    float GetGpa() const { return gpa; }
    const string &GetStudentId() const { return studentId; }
  
    virtual void Print() const override;
    virtual void IsA() const override;
    virtual void Update() override;
    // note: we choose not to redefine Person::Greeting(const string &)
    virtual void Graduate();   // newly introduced virtual fn.
    bool AddCourse(Course *);
    void PrintCourses() const;
};


Student::Student() : gpa(0.0), studentId (""), currentNumCourses(0) 
{
    for (int i = 0; i < MAXCOURSES; i++)
        courses[i] = nullptr;
    waitList = nullptr;
}

// Alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &id, Course *c) : 
                 Person(fn, ln, mi, t), Observer(), gpa(avg), studentId(id), currentNumCourses(0)
{
    for (int i = 0; i < MAXCOURSES; i++)
        courses[i] = nullptr;
    waitList = c;      // Set waitlist to Course (Subject) 
    c->Register(this); // Add the Student (Observer) to the Subject's list
}

// Another alternate constructor member function definition
Student::Student(const string &fn, const string &ln, char mi, const string &t, float avg, const string &id) : 
                 Person(fn, ln, mi, t), Observer(), gpa(avg), studentId(id), currentNumCourses(0)
{
    waitList = nullptr;   // no Course on waitlist 
    for (int i = 0; i < MAXCOURSES; i++)
        courses[i] = nullptr;
}

   
// destructor definition
Student::~Student()
{
    // Add code to remove this Student from the respective course lists
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
}

void Student::IsA() const
{
    cout << "Student" << endl;
}


bool Student::AddCourse(Course *c)
{
    // Should also check to ensure Student isn't already in Course
    if (currentNumCourses < MAXCOURSES)
    {
        courses[currentNumCourses++] = c;
        c->AddStudent(this);
        return true;
    }
    else 
    {
        // Add Student (Observer) to the Course's Waitlist (in the Subject base class)
        c->Register(this);
        waitList = c;
        return false;
    }
}


void Student::Graduate()
{
    // Assume this method is fully implemented. 
}


void Student::Update()
{
    if (waitList->GetState() == 1)  // Course state changed to 'Open' so we can now add it.
    {
        if (AddCourse(waitList))    // if success in Adding (I mean, it could have failed for several reasons) 
        {
            cout << GetFirstName() << " " << GetLastName() << " removed from waitlist and added to " << waitList->GetTitle() << endl;
            SetState(1);  // set Observer's state to 1 (e.g. we were able to add Course)
            waitList->Release(this);  // Remove Observer (Student = this) from Subject (Course's waitlist)
            waitList = 0;  // Set our link to Subject to Null
        }
    }
    // cout << "Update for : " << GetFirstName() << " " << GetLastName() << " complete" << endl;
}


void Student::PrintCourses() const
{
    cout << "Student: (" << GetFirstName() << " " << GetLastName() << ") enrolled in: " << endl;
    for (int i = 0; i < MAXCOURSES && courses[i] != 0; i++)
        cout << "\t" << courses[i]->GetTitle() << endl; 
}


void Course::PrintStudents() const
{
    cout << "Course: (" << GetTitle() << ") has the following students: " << endl;
    for (int i = 0; i < MAXSTUDENTS && students[i] != 0; i++)
        cout << "\t" << students[i]->GetFirstName() << " " << students[i]->GetLastName() << endl; 
}


int main()
{
    Course *c1 = new Course("C++", 230);  // Instantiate Courses (Title and number)
    Course *c2 = new Course("Advanced C++", 430);  
    Course *c3 = new Course("Design Patterns in C++", 550);  
    // Instantiate Students and select a course they'd like to be on the waitlist for -- to be added as soon as registration starts
    Student s1("Anne", "Chu", 'M', "Ms.", 3.9, "555CU", c1); 
    Student s2("Joley", "Putt", 'I', "Ms.", 3.1, "585UD", c1); 
    Student s3("Goeff", "Curt", 'K', "Mr.", 3.1, "667UD", c1); 
    Student s4("Ling", "Mau", 'I', "Ms.", 3.1, "55UD", c1); 
    Student s5("Jiang", "Wu", 'Q', "Dr.", 3.8, "883TU", c1); 

    cout << "Registration is Open. Waitlist Students to be added to Courses" << endl;
    c1->Open();   // Sends a message to Students that Course is Open. Students on wait-list will automatically be Added (as room allows)
    c2->Open();
    c3->Open();

    // Now that registration is open, let's try to add more courses directly
    cout << "During open registration, Students now adding more courses" << endl;
    s1.AddCourse(c2);  // Now that registration is open, Students can add Courses.
    s2.AddCourse(c2);  // Should a Course be full, the Student will be added to the Course waitlist 
    s4.AddCourse(c2);  // Note: Course inherits from Subject which keeps a list of Students interested in adding course
    s5.AddCourse(c2);  // When Course state changes to "available space in class", Students on waitlist (Observers) are Notified 
                       // to try to Add the Course. Of course, successful adding only happens as space allows. The rest stay on waitlist.

    s1.AddCourse(c3);  // If Course is full, have Course Register student to be added to wait list 
    s3.AddCourse(c3);
    s5.AddCourse(c3);

    cout << "Registration complete" << endl;
    c1->PrintStudents();
    c2->PrintStudents();
    c3->PrintStudents();

    s1.PrintCourses();
    s2.PrintCourses();
    s3.PrintCourses();
    s4.PrintCourses();
    s5.PrintCourses();

    // Implement DropCourse(). When a Student Drops a course, this event will cause Course state to become "Available Space in Course". 
    // Notify() will then be called on the Course (Subject), which will call Update() the list of Observers (students on the waitList). 
    // This Update() will indirectly allow waitlisted Students, if any, to now Add the course. 
    // Lastly, in DropCourse, remove course from Student's courselist.

    delete c1;
    delete c2;
    delete c3;

    return 0;
}

