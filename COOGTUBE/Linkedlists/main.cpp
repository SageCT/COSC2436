#include "Linkedlist.h"
// #include "DLL.h"
// #include "CLL.h"
#include <string>

using namespace std;

int main()
{
    linkedlist<string> list;

    list.addAtTail("Hello");
    list.addAtTail("Goodbye");
    list.print(cout);
    return 0;
}