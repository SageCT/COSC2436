// Extra: change I Love Cplusplus to
//(1) IlvClsls
//(2) Ivcss
//(3)Ics
//  (4) Is
//  (5) Is
// Circular Linked List implementation
// Extra Name: Extra 9_3_1

// LinkedList Linear sech and Binary seach (Extra)

#include <iostream>
#include <string>
using namespace std;
bool search(int key)
{
    node *cu = head;
    while (cu->val != key && cu->next != nullptr)
    {
        cu = cu->next;
    }

    if (cu->next == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool binary(int a[], int key, int low, int high)
{
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (key < mid)
            high = mid - 1;
        else if (key > mid)
            low = mid + 1;
        else
            return true;
        return false;
    }
}

int main()
{

    return 0;
}