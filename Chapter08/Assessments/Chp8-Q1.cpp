// (c) Dorothy R. Kirk. All Rights Reserved
// Sample Solution Chp 8, Question 1, parts a - d
// Note: we could have also chosen to store area in Shape. Here, we calculate it with CalcArea() each time.

#include <iostream>
#include <iomanip>
using std::cout;    // preferred to: using namespace std;
using std::endl;
using std::setprecision;
using std::string; 

constexpr float PI = (float) 3.14159;
constexpr int MAX = 5;

class Shape
{
private:
	string name;
public:
        // Notice that we are eliminating the default constructor interface
	Shape(string n) : name(n) { cout << "Shape constructor" << endl; } 
	const string &GetName() { return name; }
	virtual ~Shape() { cout << "Shape destructor" << endl; }
	virtual float CalcArea() = 0;
};

class Circle: public Shape
{
private:
	float radius = 0.0;
public:
        // Notice that we are eliminating the default constructor interface
	Circle(float rad) : Shape("Circle"), radius(rad) { cout << "Circle constructor" << endl; }
	~Circle() override { cout << "Circle destructor" << endl; }
	float CalcArea() override;
};

float Circle::CalcArea()
{
	return (PI * radius * radius);
}

class Triangle: public Shape
{
private:
	float base = 0.0;
	float height = 0.0;
public:
        // Notice that we are eliminating the default constructor interface
	Triangle(float, float);
	~Triangle() override { cout << "Triangle destructor" << endl; }
	float CalcArea() override;
};

Triangle::Triangle(float b, float ht): Shape("Triangle"), base(b), height(ht)
{ 
    cout << "Triangle constructor" << endl;
}
	

float Triangle::CalcArea()
{
	return (.5 * base * height);
}

class Square: public Shape
{
private:
	float side = 0.0;
public:
        // Notice that we are eliminating the default constructor interface
	Square(float);
	~Square() override { cout << "Square destructor" << endl; }
	float CalcArea() override;
};

Square::Square(float len): Shape("Square"), side(len)
{ 
    cout << "Square constructor" << endl;
}
	

float Square::CalcArea()
{
	return (side * side);
}

int main()
{
	Shape *shapes[MAX] = { };  // initialize to nullptrs

	shapes[0] = new Circle(2.2);
	shapes[1] = new Square(4.2);
	shapes[2] = new Triangle(1.2, 2.3);
	shapes[3] = new Triangle(2.0, 3.0);
	shapes[4] = new Circle(5.0);

	cout.setf(std::ios::showpoint);    // show decimal points even for values with .00 after decimal point

        // Instead of the following looping style, we can instead use the style below this grouping.
	// for (int i = 0; i < MAX; i++)
	// {
        //      cout << "The " << shapes[i]->GetName();
        // 	cout << " has an area of " << setprecision(3) << shapes[i]->CalcArea() << endl;
	// }
        
        // Here is a more modern style loop to process the shape:
        for (auto *iter : shapes)
        {
                cout << "The " << iter->GetName(); 
                cout << " has an area of " << setprecision(3) << iter->CalcArea() << endl;
        }

        // Instead of the following looping style to deallocate memory:
	// for (int i = 0; i < MAX; i++)
        //	delete shapes[i];
    
        // We can use a more modern style:
	for (auto iter : shapes)
		delete iter; 

	return 0;
}
