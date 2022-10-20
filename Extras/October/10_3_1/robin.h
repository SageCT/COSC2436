#include <iostream>
#include <string>

using namespace std;

struct node
{
    string job;
    int totalMin;
    int remainMin;
    node *next;
};

class robin
{
private:
    node *front;
    node *back;

public:
    robin();
    bool isEmpty() const { return (front == nullptr); }
    void enq(string, int, int);
    node *deq();
    void print();
};

robin::robin()
{
    front = back = new node();
    front->next = back;
    back->next = front;
}

void robin::enq(string st, int a, int b)
{
    node *temp = new node();
    temp->job = st, temp->totalMin = a, temp->remainMin = b, temp->next = nullptr;

    if (isEmpty())
    {
        front = temp;
        back = temp;
    }
    else
    {
        back->next = temp;
        back = temp;
    }
}

node *robin::deq()
{
    if (front != nullptr)
    {
        node *temp = front;
        front = front->next;

        return front;
    }

    return nullptr;
}

void robin::print()
{
    while (front != nullptr)
    {
        cout << "Job Name: " << front->job << " Job Remaining Time " << front->remainMin << " Job Total Time " << front->totalMin << endl;
        deq();
    }

    //     node *toPrint = deq();
    //     cout << "Job Name: " << toPrint->job << " Job Remaining Time: " << toPrint->remainMin << " Job Total Time: " << toPrint->totalMin << endl;
    //     cout << "\n";
}