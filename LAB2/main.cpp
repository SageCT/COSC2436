#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

template <typename T>
struct node
{
    T data;
    node<T> *next;
};

template <typename T>
class linkedlist
{
private:
    node<T> *head;
    int size;

public:
    linkedlist();
    ~linkedlist();
    bool isEmpty() { return head == nullptr; }
    int getSize() { return size; }
    void addAtHead(T value); // Need to add... added
    void addAtTail(T value);
    void removeAtHead(); // Need to add... added
    void removeAtTail();
    void addAtPos(T value, int pos);
    void print(ostream &out);
};

template <typename T>
linkedlist<T>::linkedlist()
{
    head = nullptr;
    size = 0;
}

template <typename T>
linkedlist<T>::~linkedlist()
{
    node<T> *cu = head;
    while (cu != nullptr)
    {
        node<T> *temp = cu;
        cu = cu->next;
        delete temp;
    }
}

template <typename T>
void linkedlist<T>::addAtHead(T value)
{
    node<T> *temp = new node<T>();
    temp->data = value;
    temp->next = head;

    head = temp;
    size++;
}

template <typename T>
void linkedlist<T>::addAtTail(T value)
{
    node<T> *temp = new node<T>();
    temp->data = value;
    temp->next = nullptr;

    node<T> *cu = head;
    if (cu == nullptr)
    {
        head = temp;
    }
    else
    {
        while (cu->next != nullptr)
        {
            cu = cu->next;
        }
        cu->next = temp;
    }
    size++;
}

template <typename T>
void linkedlist<T>::removeAtHead()
{
    if (head == nullptr)
        return;
    else
    {
        delete head;
        head = head->next;
        size--;
    }
}

template <typename T>
void linkedlist<T>::removeAtTail()
{
    node<T> *cu = head;
    node<T> *prev = nullptr;
    if (cu == nullptr)
        return;
    else if (cu->next == nullptr)
    {
        head = nullptr;
    }
    else
    {
        while (cu->next != nullptr)
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = nullptr;
        delete cu;
    }
    size--;
}

template <typename T>
void linkedlist<T>::print(ostream &out)
{
    node<T> *cu = head;
    while (cu != nullptr)
    {
        (cu->next == nullptr) ? (out << cu->data) : (out << cu->data << " ");
        cu = cu->next;
    }
}

template <typename T>
void linkedlist<T>::addAtPos(T value, int pos)
{
    node<T> *temp = new node<T>();
    temp->data = value;
    temp->next = nullptr;

    node<T> *cu = head;
    node<T> *prev = nullptr;

    if (pos > size)
        return;
    else if (pos == 0)
    {
        head = temp;
        temp->next = cu;
    }
    else
    {
        for (int i = 0; i < pos; i++)
        {
            prev = cu;
            cu = cu->next;
        }
        prev->next = temp;
        temp->next = cu;
    }
    size++;
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));

    // ifstream input("input1.txt");
    // ofstream out("output1.txt");
    if (input.peek() != EOF)
    {
        string in, type;
        bool headOrTail;
        vector<string> lines;

        while (getline(input, in))
        {
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue;
            lines.push_back(in);
        }

        linkedlist<string> list1;

        if (lines.at(1) == "head")
            headOrTail = true;
        else if (lines.at(1) == "tail")
            headOrTail = false;

        for (int x = 2; x < lines.size(); x++)
        {
            if (lines.at(x) == "removehead")
                list1.removeAtHead();

            else if (lines.at(x) == "removetail")
                list1.removeAtTail();

            else
                (headOrTail) ? (list1.addAtHead(lines.at(x))) : (list1.addAtTail(lines.at(x)));
        }

        list1.print(out);
    }
    return 0;
}