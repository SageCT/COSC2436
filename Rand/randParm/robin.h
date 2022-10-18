#include <string>
using namespace std;

struct node
{
    int job;
    int rem;
    int count;
    int start;
    node *next;
};

class robin
{
private:
    node *front;
    node *back;

public:
    robin()
    {
        front = back = nullptr;
    }
    void enq(node *temp)
    {
        temp->next = nullptr;
        if (front == nullptr)
        {
            front = temp;
            back = temp;
        }
        else if (front->next == nullptr)
        {
            back = temp;
            front->next = back;
        }
        else
        {
            back->next = temp;
            back = temp;
        }
    }
    node *deq()
    {
        node *temp = front;
        front = front->next;
        return temp;
    }
    bool empty()
    {
        return (front == nullptr);
    }
    void print()
    {
    }
};