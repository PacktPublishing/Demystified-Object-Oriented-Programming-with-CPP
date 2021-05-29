// (c) Dorothy R. Kirk. All Rights Reserved.
// Purpose: Review namespaces (adding new and augmenting existing namespaces)
// This example explores ambiguities of opening multiple namespaces with duplicative elements

#include <iostream>

// using namespace std;   // This statement brings in entire namespace std
using std::cout;          // Instead, we can bring in individual elements....
using std::endl;          // See book discussion as to why this is preferred.

namespace DataTypes
{
    int total;

    class LinkList
    {   // full class definition ...
    };

    class Stack
    {   // full class definition ...
    };
};

namespace AbstractDataTypes
{
    class Stack
    {   // full class definition ...
    };

    class Queue
    {   // full class definition ...
    };
};

namespace AbstractDataTypes
{
    int total;

    class Tree
    {   // full class definition ...
    };
};


int main()
{

    using namespace AbstractDataTypes;  // activate namespace
    using DataTypes::LinkList;   // activate only LinkList
    
    LinkList list1;    // LinkList is found in DataTypes
    Stack stack1;    // Stack is found in AbstractDataTypes
 
    total = 5;       // from active AbstractDataTypes
    DataTypes::total = 85;   // specify non-active member
     
    cout << "total " << total << "\n";
    cout << "DataTypes::total " << DataTypes::total << endl;
    
    return 0;
}

