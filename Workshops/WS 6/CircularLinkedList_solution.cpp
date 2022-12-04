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
    node *newNode = new node();
    newNode->data = val;
    newNode->next = head;

    head = newNode;
    if (tail == nullptr)
    { // runs this condition if adding the first node to the list
        tail = newNode;
    }

    tail->next = head; // links last node to the first node
}

void CircularLinkedList::insertAtEnd(int val)
{
    node *newNode = new node();
    newNode->data = val;
    newNode->next = head;

    if (head == nullptr)
    { // if linked list was previously empty
        head = tail = newNode;
    }
    else
    { // otherwise, add to the end - O(n)
        tail->next = newNode;
        tail = newNode;
    }

    tail->next = head; // links last node to the first node
}

void CircularLinkedList::insertAtPos(int val, int pos)
{
    if (pos < 0 || head == nullptr)
    { // check bounds or if list if empty
        return;
    }
    else if (pos == 0)
    { // starting at index 0
        insertAtHead(val);
    }
    else
    { // starts at the second node
        node *newNode = new node;
        newNode->data = val;

        node *temp = head;
        do
        {
            if (pos == 1)
            { // stop condition: if we reach a pos in bounds, we insert
                newNode->next = temp->next;
                temp->next = newNode;
                if (temp == tail)
                {
                    newNode = tail;
                }
                break;
            }
            pos--; // decrement pos w every iteration so we know which pos to add at
            temp = temp->next;
        } while (temp != head);
    }
}

void CircularLinkedList::deleteAtHead()
{
    if (head != nullptr)
    { // check if list is not empty
        node *temp = head;
        if (head->next == head)
        { // if we have a list of one node
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            tail->next = head;
        }

        delete temp;
    }
}

void CircularLinkedList::deleteAtEnd()
{
    if (head != nullptr)
    { // check if list is not empty
        if (head->next == head)
        { // if we have a list of one node
            head = tail = nullptr;
        }
        else
        {
            node *temp = head;
            while (temp->next != tail)
            { // stop at the node before tail bc we delete the last node, which is currently set as tail
                temp = temp->next;
            }
            delete temp->next; // delete the last node
            tail = temp;
            tail->next = head;
        }
    }
}

void CircularLinkedList::deleteByPos(int pos)
{
    if (pos < 0 || head == nullptr)
    { // check bounds or if list is empty
        return;
    }
    else if (pos == 0)
    { // starting at index 0
        deleteAtHead();
    }
    else
    { // starts at second node
        node *prev = head;
        node *curr = head->next;
        while (curr != head)
        {
            if (pos == 1)
            {                            // stop condition: if we reach a pos in bounds, we delete
                prev->next = curr->next; // change link to skip curr (we're deleting curr)
                if (curr == tail)
                { // if we're deleting the last node
                    tail = prev;
                }
                delete curr;
            }
            pos--; // decrement pos w every iteration so we know which pos to add at
            prev = curr;
            curr = curr->next;
        }
    }
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

    list.insertAtHead(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtHead(5);
    list.print();

    std::cout << std::endl;

    list.insertAtPos(15, 2);
    list.insertAtPos(25, 6);
    list.insertAtPos(5, -1);
    list.insertAtPos(2, 0);
    list.insertAtPos(40, 6);
    list.print();

    std::cout << std::endl;

    list.deleteAtHead();
    list.deleteAtEnd();
    list.print();

    std::cout << std::endl;

    list.deleteByPos(2);
    list.deleteByPos(5);
    list.deleteByPos(-2);
    list.print();
}