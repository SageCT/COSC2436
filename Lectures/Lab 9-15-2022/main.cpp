using namespace std;
// function for recursively couting the number of nodes in a singly linked list
int count(node *n)
{
    if (n == nullptr)
    {
        return 0;
    }
    return 1 + count(n->next);
}

// Find where a noce is peak in a doubly linked list, peak means the nodes previous and next are less than the current one
void peak(node *head)
{
    if (head == nulltr || head->next == nullptr)
        return;
}

int main()
{
    return 0;
}