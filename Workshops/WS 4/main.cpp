#include <iostream>
#include <algorithm>
#include "LinkedList.h"

using namespace std;

template <typename T>
class LinkedList
{
private:
    Node<T> *head;

public:
    LinkedList();
    ~LinkedList();
    void insert(int index, const T &item);
    bool remove(const T &token);
    string const toString();
};

template <typename T>
class Node
{
private:
    Node<T> *next;

public:
    <T> value;
};

int main()
{
    LinkedList<int> list;

    return 0;
}