#include <iostream>

struct node
{
    int data;
    node *next;
};

class CircularLinkedList
{
private:
    node *head;
    node *tail;

public:
    CircularLinkedList() { head = tail = nullptr; }
    node *getHead() { return head; }
    void insertAtHead(int val);
    void insertAtEnd(int val);
    void insertAtPos(int val, int pos);
    void deleteAtHead();
    void deleteAtEnd();
    void deleteByPos(int pos);
    void print();
};

void CircularLinkedList::insertAtHead(int val)
{
    // implement
    node *temp;
    temp->data = val;
    temp->next = head;

    head = temp;
}

void CircularLinkedList::insertAtEnd(int val)
{
    // implement

    node *temp;
    temp->data = val;
    temp->next = head;

    tail = temp;
}

void CircularLinkedList::insertAtPos(int val, int pos)
{
    // implement (assume index starts at 0)
    node *temp;
    node *curr;
    node *prev;

    curr = prev = head;
    temp->data = val;

    // Search for the position with while loop
    while (pos > 0)
    {
        if(pos == 1)
            prev = curr;
        curr = curr->next;
        pos--;
    }

    if (head == tail){
        head = tail = temp;
    }

    else
    {
        prev->next = temp;
        temp->next = curr;   
    }
}

void CircularLinkedList::deleteAtHead()
{
    // implement
    tail->next = head->next;
    delete head;
    head = head->next;
}

void CircularLinkedList::deleteAtEnd()
{
    // implement

    
}

void CircularLinkedList::deleteByPos(int pos)
{
    // implement (assume index starts at 0)
}

void CircularLinkedList::print()
{
    if (head != nullptr)
    {
        node *temp = head;
        do
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
    }
}

int main()
{
    CircularLinkedList list;

    // list.insertAtHead(10);
    // list.insertAtEnd(20);
    // list.insertAtEnd(30);
    // list.insertAtHead(5);
    // list.print();

    // std::cout << std::endl;

    // list.insertAtPos(15, 2);
    // list.insertAtPos(25, 6);
    // list.insertAtPos(5, -1);
    // list.insertAtPos(2, 0);
    // list.insertAtPos(40, 6);
    // list.print();

    // std::cout << std::endl;

    // list.deleteAtHead();
    // list.deleteAtEnd();
    // list.print();

    // std::cout << std::endl;

    // list.deleteByPos(2);
    // list.deleteByPos(5);
    // list.deleteByPos(-2);
    // list.print();
}