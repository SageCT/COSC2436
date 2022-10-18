#include <iostream>

struct node
{
    string job;
    int totMin;
    int remMin;
};

class robin
{
private:
    node *front;
    node *back;

public:
    robin();
    void enqueue(string, int, int);
    void dequeue();
    void print() const;
};