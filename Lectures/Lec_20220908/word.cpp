#include <iostream>
#include "word.h"

using namespace std;

void word::addatend(char x)
{
    // 1- Create
    letter *temp = new letter;
    // 2 - Fill
    temp->l = x;
    temp->next = 0;
    // 3- Location and update pointers
    if (head == 0)
    {
        head = tail = temp;
    }

    else
    {
        tail->next = temp;
        tail = tail->next;
    }
}

void word::print()
{
    letter *cu = head;
    while (cu != nullptr)
    {
        cout << cu->l << endl;
        cu = cu->next;
    }
}

void word::deletefrombeg()
{
    // 1- Mark
    letter *temp = head;
    // 2 - Empty
    cout << "Deleting... " << temp->l << endl;
    // 3 - Update
    head = head->next;
    delete temp;
}

void word::printR(letter *cu)
{
    if (cu == nullptr)
        return;
    else
    {
        cout << cu->l << endl;
        printR(cu->next);
    }
}

letter *word::gethead() { return head; }

bool word::search(char key)
{
    letter *cu = head;
    while (cu->l != key && cu != 0)
        cu = cu->next;
    if (cu->l == key)
        return true;
    else
        return false;
}
