#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
// Linked List example/possible extra

// Individual nodes
struct pearl
{
    int color;
    float gpa;
    pearl *hole;
};

// List Class for the nodes
class necklace
{
private:
    pearl *head;

public:
    necklace() { head = 0; }
    void addPearl(int c);
    void print();
};

int main()
{
    necklace mine;
    mine.addPearl(1);
    mine.addPearl(5);
}

// Create a linked list pearl