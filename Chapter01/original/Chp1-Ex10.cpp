// (c) 2020 Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review simple enum types

#include <iostream>

using namespace std;

enum day {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

enum workDay {Mon = 1, Tues, Wed, Thurs, Fri};

int main()
{
    day birthday = Monday;
    workDay payday = Fri;

    cout << "Birthday is " << birthday << endl;
    cout << "Payday is " << payday << endl;

    return 0;
}
