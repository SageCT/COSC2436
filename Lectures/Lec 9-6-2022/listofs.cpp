#include <iostream>
#include "listofs.h"

using namespace std;

listofs::listofs()
{
    head = nullptr;
}

bool listofs::isempty()
{
    if (head == 0)
        return true;

    else
    {
        return false;
    }
}

void listofs::addatbeg(int a, float b)
{
    if (isempty())
    {
        head = new st;
        head->ps = a;
        head->gpa = b;
        head->next = 0;
    }
}

void addatbeg(int, float);
void addatend(int, float);