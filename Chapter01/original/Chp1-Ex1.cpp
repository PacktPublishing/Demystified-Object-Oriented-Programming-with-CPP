// (c) 2020 Dorothy R. Kirk. All Rights Reserved. 
// Purpose: To illustrate simple I/O with iostreams

#include <iostream>

using namespace std;

int main()
{
    char name[20];
    int age;
    cout << "Please enter a name and an age: ";
    cin >> name >> age;
    cout << "Hello " << name;
    cout << ". You are " << age << " years old." << endl;
    return 0;
}
