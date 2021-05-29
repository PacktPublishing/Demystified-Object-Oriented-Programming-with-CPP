// (c) Dorothy R. Kirk. All Rights Reserved. 
// Purpose: To illustrate very simple I/O with iostreams
// Don't worry -- we'll add safety measures in the very next example (see comment below)

#include <iostream>

using std::cin;       // preferred to: using namespace std;
using std::cout;
using std::endl;

int main()
{
    char name[20];    // caution, uninitialized array of char 
    int age = 0;
    cout << "Please enter a name and an age: ";
    // we'll see in the next example how to ensure we don't overflow the name buffer
    cin >> name >> age;
    cout << "Hello " << name;
    cout << ". You are " << age << " years old." << endl;
    return 0;
}

