#include <string>
#include <iostream>
// #include "stack.h"
#include "queue.h"

using namespace std;

int main()
{
    queue q;
    for (int i = 1; i <= 10; i++)
        q.enqueue(i);

    q.print(cout);
    return 0;
}