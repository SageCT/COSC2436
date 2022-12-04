#include <string>
#include <iostream>
#include "stack.h"
// #include "queue.h"

using namespace std;

int main()
{
    Stack s;

    s.push(0);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    s.print(cout);

    return 0;
}