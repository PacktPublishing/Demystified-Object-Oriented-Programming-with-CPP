// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: To demonstrate a simple template class -- an Array of any data type.
//          This baseline class employs bounds checking and can easily be augmented to allow resizing. 
 
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

template <class Type>  // template class preamble
class Array
{
private:
    int numElements;
    Type *contents;
public:
    Array(int size) : numElements(size) { contents = new Type [size]; }
    ~Array() { delete contents; }
    void Print() const
    {
        for (int i = 0; i < numElements; i++)
            cout << contents[i] << " ";
        cout << endl;
    }
    Type &operator[](int index) 
    {
        if (index < numElements) return contents[index];
        else cout << "Out of bounds" << endl;
    }
    void operator+(Type);
};

template <class Type>
void Array<Type>::operator+(Type item)
{
    // resize array if necessary, add new data element and increment numElements
}

int main()
{
    Array<int> a1(3);  // create an ArrayInt of 3 elements
    a1[2] = 12;
    a1[1] = 70;
    a1[0] = 2;
    a1.Print();
}

