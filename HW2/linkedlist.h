#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return size; }
    node<T> getHead() const { return head; }
    void addAtHead(T value); // Need to add... added
    void addAtTail(T value);
    void removeAtHead(); // Need to add... added
    void removeAtTail();
    void removeAtPos(int pos); // New remove to remove from searched index
    void addAtPos(T value, int pos);
    node<T> *returnAtPos(int pos);       // New returns pointer to node at position
    int search(string toFind) const;     // New Search to find index
    void swap(node<T> *n1, node<T> *n2); // New NEEDS REWORK TO USE ADDATPOS AND DELETEATPOS!
    T searchData(string toFind) const;
    void sort(string type);
    void print(std::ostream &out) const;
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
void linkedlist<T>::removeAtPos(int pos)
{
    int currIndex = 0;
    node<T> *curr = head;
    node<T> *prev = nullptr;
    node<T> *next = head->next;

    if (pos == 0)
    {
        removeAtHead();
    }

    else
    {

        while (currIndex < pos)
        {
            prev = curr;
            next = next->next;
            curr = curr->next;
            currIndex++;
        }

        if (currIndex == pos)
        {
            prev->next = next;
            curr->next = nullptr;
            delete curr;
        }
        size--;
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

    if (pos == 0)
    {
        head = temp;
        temp->next = cu;
    }

    else if (pos > size)
        return;

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

template <typename T>
int linkedlist<T>::search(string toFind) const
{
    node<T> *curr = head;
    int index = 0;
    while (curr != nullptr)
    {
        if (curr->data.find(toFind) != string::npos)
            return index;
        curr = curr->next;
        index++;
    }
    return -1;
}

template <typename T>
node<T> *linkedlist<T>::returnAtPos(int pos)
{
    node<T> *curr = head;
    while (pos > 0)
    {
        curr = curr->next;
        pos--;
    }
    return curr;
}

template <typename T>
T linkedlist<T>::searchData(string toFind) const
{
    node<T> def;
    def.data = nullptr;
    def.next = nullptr;
    node<T> *curr = head;
    int index = 0;
    while (curr != nullptr)
    {
        if (curr->data.find(toFind) != string::npos)
            return curr->data;
        curr = curr->next;
        index++;
    }
    return def.data;
}

template <typename T>
void linkedlist<T>::sort(string type)
{
    if (type == "id")
    {
        int i, j, n = getSize();
        for (i = 0; i < n; i++)
            for (j = 0; j < n - i - 1; j++)
                if (stoi(returnAtPos(j)->data.substr(returnAtPos(j)->data.find(":") + 1, 4)) > stoi(returnAtPos(j + 1)->data.substr(returnAtPos(j + 1)->data.find(":") + 1, 4)))
                    swap(returnAtPos(j), returnAtPos(j + 1));
    }

    else if (type == "username")
    {
        int i, j, n = getSize();
        int startIndex1, startIndex2, endIndex1, endIndex2, smallestLen;
        string string1, string2;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                startIndex1 = returnAtPos(j)->data.find("username:") + 9;
                endIndex1 = returnAtPos(j)->data.find(";", startIndex1);
                string1 = returnAtPos(j)->data.substr(startIndex1, endIndex1 - startIndex1);

                startIndex2 = returnAtPos(j + 1)->data.find("username") + 9;
                endIndex2 = returnAtPos(j + 1)->data.find(";", startIndex2);
                string2 = returnAtPos(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2);

                if (string1.compare(string2) > 0)
                {
                    swap(returnAtPos(j), returnAtPos(j + 1));
                }

                else if (string1.compare(string2) == 0)
                {
                    startIndex1 = returnAtPos(j)->data.find("score:") + 6;
                    endIndex1 = returnAtPos(j)->data.find(";", startIndex1);
                    string1 = returnAtPos(j)->data.substr(startIndex1, endIndex1 - startIndex1);

                    startIndex2 = returnAtPos(j + 1)->data.find("score:") + 6;
                    endIndex2 = returnAtPos(j + 1)->data.find(";", startIndex2);
                    string2 = returnAtPos(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2);

                    int score1 = stoi(string1), score2 = stoi(string2);
                    if (score1 < score2)
                        swap(returnAtPos(j), returnAtPos(j + 1));
                }
            }
        }
    }

    else if (type == "grade")
    {
        int i, j, n = getSize();
        int startIndex1, startIndex2, endIndex1, endIndex2, smallestLen;
        string string1, string2;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                startIndex1 = returnAtPos(j)->data.find("grade:") + 5;
                endIndex1 = returnAtPos(j)->data.find(";", startIndex1);
                string1 = returnAtPos(j)->data.substr(startIndex1, endIndex1 - startIndex1);

                startIndex2 = returnAtPos(j + 1)->data.find("grade:") + 5;
                endIndex2 = returnAtPos(j + 1)->data.find(";", startIndex2);
                string2 = returnAtPos(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2);

                if (string1 > string2)
                    swap(returnAtPos(j), returnAtPos(j + 1));
            }
        }
    }

    else if (type == "score")
    {
        // Need to add bubblesort
        int i, j, n = getSize();

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                int startIndex1 = returnAtPos(j)->data.find("score:") + 6, endIndex1 = returnAtPos(j)->data.find(";", startIndex1);
                string string1 = returnAtPos(j)->data.substr(startIndex1, endIndex1 - startIndex1);

                int startIndex2 = returnAtPos(j + 1)->data.find("score:") + 6, endIndex2 = returnAtPos(j + 1)->data.find(";", startIndex2);
                string string2 = returnAtPos(j + 1)->data.substr(startIndex2, endIndex2 - startIndex2);

                int score1 = stoi(string1), score2 = stoi(string2);
                if (score1 < score2)
                    swap(returnAtPos(j), returnAtPos(j + 1));
            }
        }
    }
}

template <typename T>
void linkedlist<T>::swap(node<T> *n1, node<T> *n2)
{

    int index1 = search(n1->data), index2 = search(n2->data);
    T tempVar1 = returnAtPos(index1)->data;

    addAtPos(returnAtPos(index2)->data, index1);
    removeAtPos(index1 + 1);

    addAtPos(tempVar1, index2);
    removeAtPos(index2 + 1);
}

template <typename T>
void linkedlist<T>::print(ostream &out) const
{
    node<T> *cu = head;
    while (cu != nullptr)
    {
        (cu->next == nullptr) ? (out << cu->data) : (out << cu->data << endl);
        cu = cu->next;
    }
}