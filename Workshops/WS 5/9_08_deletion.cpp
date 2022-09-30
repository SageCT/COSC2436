#include <iostream>

struct node
{
    int data;
    node *next;
};

class LinkedList
{
private:
    node *head;

public:
    LinkedList();
    void insert(int val);
    node *deletion(int val);
    node *deleteRec(node *curr, int val);
    void reverse();
    node *reverseRec(node *temp);
    void print();
    node *getHead() { return head; }
    void setHead(node *newHead) { head = newHead; }
};

LinkedList::LinkedList()
{
    head = nullptr;
}

void LinkedList::insert(int val)
{
    node *newNode = new node();
    newNode->data = val;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else if (newNode->data < head->data)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        node *temp = head;
        while (temp->next != nullptr)
        {
            if (newNode->data < temp->next->data)
            {
                break;
            }
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

node *LinkedList::deletion(int val)
{
    // implement iteratively

    node *temp;
    if (head->next != nullptr)
    {
        node *prev, *curr;
        while (head->next != nullptr && curr->data != val)
        {
            prev = head;
            curr = head->next;
        }
        if (curr->data == val)
        {
            temp = curr;
        }
    }
    else
    {

        delete temp;
    }
}

node *LinkedList::deleteRec(node *curr, int pos)
{
    // implement recursively
    if (pos < 0)
    {
        node *temp = curr;
        delete curr;
    }
    deleteRec(curr->next, --pos);
}

void LinkedList::reverse()
{
    // implement iteratively
    node *curr, *prev, *nextNode;

    while (nextNode != nullptr)
    {
    }
}

node *LinkedList::reverseRec(node *temp)
{
    // implement recursively
}

void LinkedList::print()
{
    node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int main()
{
    LinkedList list;
    list.insert(10);
    list.print();

    list.insert(20);
    list.print();

    list.insert(15);
    list.print();

    list.insert(17);
    list.print();

    list.insert(30);
    list.print();

    list.insert(5);
    list.print();

    list.insert(4);
    list.print();

    list.insert(12);
    list.print();

    list.insert(40);
    list.print();

    // std::cout << std::endl;

    // list.deletion(4);
    // list.print();

    // list.deletion(12);
    // list.print();

    // list.deletion(40);
    // list.print();

    // list.deletion(60);
    // list.print();

    // std::cout << std::endl;

    // list.setHead(list.deleteRec(list.getHead(), 0));
    // list.print();

    // list.setHead(list.deleteRec(list.getHead(), 2));
    // list.print();

    // list.setHead(list.deleteRec(list.getHead(), 3));
    // list.print();

    // list.setHead(list.deleteRec(list.getHead(), 5));
    // list.print();

    // list.setHead(list.deleteRec(list.getHead(), -1));
    // list.print();

    // std::cout << std::endl;

    // list.reverse();
    // list.print();

    // std::cout << std::endl;
    // list.reverseRec(list.getHead());
    // list.print();
}