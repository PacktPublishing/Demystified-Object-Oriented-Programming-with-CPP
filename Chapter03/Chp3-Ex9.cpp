// (c) Dorothy R. Kirk. All Rights Reserved
// Purpose: To illustrate void pointers
// Note: void *'s must be used with extreme caution. 
// They are illustrated because you may see them in existing code. You may prefer to use a template to genericize a type 
// (we'll later see that a template will expand for each actual type, whereas a void * does not)

#include <iostream>

using std::cout;    // preferred to: using namespace std;
using std::endl;

int main()
{
    void *unspecified = nullptr;  // the void * may point to any data type
    int *x = nullptr;

    unspecified = new int;  // the void * now points to an int

    // the void * must be vase to an int * before it is dereferenced
    *(static_cast<int *>(unspecified)) = 89;

    // let x point to the memory which unspecified points to
    x = static_cast<int *> (unspecified);

    cout << *x << " " << *(static_cast<int *>(unspecified)) << endl;

    delete static_cast<int *>(unspecified);

    return 0;
}
