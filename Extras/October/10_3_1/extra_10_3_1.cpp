/*
    Queue
    Four jobs
    Each Job is different
    J1 - 15 min
    J2 - 30 min
    J3 - 6 min
    J4 - 22 min
    Create a Queue and insert these jobs
    Node attributes:
        Job, Time, Remaining Time
        str, int , int
    Process:
    Deq -> Update -> Enq
    Remove from front of queue -> subtract time from remaining time -> push to end
    If no remaining minutes, do not push

    Output:
    How long does it take to finish all jobs? (SET COUNTER)
    J1 Started time & finishing time
    J2 started time & finishing time
    J3 Started time & finishing time
    J4 Started time & finishing time
*/

#include "robin.h"
#include <random>

using namespace std;

// RoundRobin
int main()
{
    // Create a queue and fill jobs randomly
    int counter = 0;
    int totalTime = 100;
    int remainingTime = totalTime;
    robin rr;

    // for ... or while loop to enqueue
    // Generate a random value
    while (counter++ < 5)
        rr.enq("J" + to_string(counter), (rand() % 10) + 1, totalTime);

    // counter = 0; // Count # of minutes
    // ct1 = when j1 started ct1_e when j1 ended

    // Remaining time minus total time

    rr.print();
    rr.print();

    rr.roundR(remainingTime);
    return 0;
}