#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"
#include "queue.h"
#include "stack.h"

using namespace std;

int main()
{
    //TESTING QUEUE
    queue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);

    q.print(cout);

    q.dequeue();

    q.print(cout);

    //TESTING STACK
    return 0;
}