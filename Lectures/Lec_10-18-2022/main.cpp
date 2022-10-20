// Q1 Sorting, Q2 Doubly LinkedList, Q3 Stacks, Q4 Queue, Q5 Heap, each question will be 20% of the exam
// Challenge for Ex 2 --> >75 = 2 homework regrades... <75 2nd largest improvement gets regraded on homework

// Extra 10_3_1 - Create a queue and insert a job variable
//      Job1... Job4, total time needed to finish job, remaining time
//

#include <stdLib.h>
#include "robin.h"

// RoundRobin
int main()
{
    // Create a queue and fill jobs randomly
    robin rr;

    // for ... or while loop to enqueue
    // Generate a random value
    rr.enqueue(1, 30, 30);

    int counter = 0; // Count # of minutes
    // ct1 = when j1 started ct1_e when j1 ended

    // keep dequeuing updating

    int round = 3; // Round = rand()%5; or ask user
    return 0;
}