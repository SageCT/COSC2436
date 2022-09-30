#include "dlc.h"

void dlc::addatend(char x)
{
    node *temp = new node;
    temp->l = x;

    temp->prev = tail;
    temp->next = 0;
    temp->next = temp;
    tail = temp;
}

char dlc::delfrombeg()
{
    // mark
    node *temp = head;

    // empty
    char rem = temp->l;

    // update links
    head = head->next;
    head->prev = 0;
    delete temp;
    return rem;
}

void dlc::print(node *)
{
}