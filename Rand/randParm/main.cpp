/*
Q1 sorting
Q2 Double Linkedlist
Q3 Stack
Q4 Queue
Q5 Heap

extra 10_3_1 - Queue to organize a shift
*/
#include "robin.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // create a queue and fill jobs randomly
    cout << "How many jobs are there?" << endl;
    int num;
    cin >> num;
    robin rr;
    vector<int> arr;
    int total = 0;
    for (int i = 0; i < num; i++)
    {
        cout << "What is the time for the job?" << endl;
        int t;
        cin >> t;
        node *temp = new node();
        temp->job = i;
        temp->rem = t;
        temp->count = 0;
        temp->start = i * 3;
        rr.enq(temp);
    }
    while (!rr.empty())
    {
        node *temp = rr.deq();
        cout << temp->job << endl;
        if (temp->count == 0)
        {
            temp->count += temp->start;
            temp->rem -= 3;
            rr.enq(temp);
            total += 3;
        }
        else if (temp->rem - 3 <= 0)
        {
            arr[temp->job] = temp->count + 3 + (temp->rem - 3);
            total += 3 + (temp->rem - 3);
        }
        else
        {
            temp->count += 3;
            temp->rem -= 3;
            rr.enq(temp);
            total += 3;
        }
    }
    for (int i = 0; i < num; i++)
    {
        cout << "Job " << i + 1 << " Time: " << arr[i] << endl;
    }
    cout << "Total Time: " << total << endl;
}