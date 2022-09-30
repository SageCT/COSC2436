#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Creating a linkedList variable
struct st
{
    int ps;
    float gpa;
    st *next;
};

class listofs
{
private:
    st *head;

public:
    listofs();
    bool isempty();
    void addatbeg(int a, float b);
    void addatend();
    void print();
    // Void search
    // Addmiddleposition
    //  addmiddlevalue
    //  delete from beg - mid - end
};