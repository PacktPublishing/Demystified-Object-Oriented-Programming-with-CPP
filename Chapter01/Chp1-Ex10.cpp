// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review simple enum types

#include <iostream>

using std::cout;   // preferred to: using namespace std;
using std::endl;
using std::string;

enum day {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

enum workDay {Mon = 1, Tues, Wed, Thurs, Fri};

// strongly typed enums default to int, but can be any integral type: int, char, short int, long int, bool     

enum struct WinterHoliday { Diwali, Hanukkah, ThreeKings, WinterSolstice, StLucia, StNicholas, Christmas, Kwanzaa };

enum class Holiday : short int { NewYear = 1, MLK, Memorial, Independence, Labor, Thanksgiving };

int main()
{
    day birthday = Monday;
    workDay payday = Fri;

    WinterHoliday myTradition = WinterHoliday::StNicholas; 
    Holiday favorite = Holiday::NewYear;

    cout << "Birthday is " << birthday << endl;
    cout << "Payday is " << payday << endl;

    cout << "Traditional Winter holiday is " << static_cast<int> (myTradition) << endl;
    cout << "Favorite holiday is " << static_cast<short int> (favorite) << endl;

    return 0;
}

