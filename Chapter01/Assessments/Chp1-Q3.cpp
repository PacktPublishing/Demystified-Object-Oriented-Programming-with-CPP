// (c) Dorothy R. Kirk. All Rights Reserved.
// Chapter 1, Question 3 -- Sample Solution

// Create a simple program using a struct or a class to make a user defined type 
// for Book. Add data members for title, author, and number of pages. Create two 
// variables of type Book and use the dot operator . to fill in the data members
// for each such instance. Use iostreams to both prompt the user for input values, and
// to print each Book instance when complete. Use only features covered in this chapter.

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::cin;
using std::endl;
using std::string;

class Book
{
public:
    string title;
    string author;
    int numPages;
};

int main()
{
    Book b1;
    cout << "Please enter book title <one word>: ";
    cin >> b1.title;
    cout << "Please enter book author <lastname>: ";
    cin >> b1.author;
    cout << "Please enter book number of pages: ";
    cin >> b1.numPages;
    cout << b1.title << " with author: " << b1.author << " with page count: " << b1.numPages << endl;

    Book b2;
    cout << "Please enter book title <one word>: ";
    cin >> b2.title;
    cout << "Please enter book author <lastname>: ";
    cin >> b2.author;
    cout << "Please enter book number of pages: ";
    cin >> b2.numPages;
    cout << b2.title << " with author: " << b2.author << " with page count: " << b2.numPages << endl;
    return 0;
}


