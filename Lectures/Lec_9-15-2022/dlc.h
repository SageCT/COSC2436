class dlc
{
private:
    node *head, *tail;

public:
    dlc() { head = tail = nullptr; }
    node *gethead() { return head; }
    node *gettail() { return tail; }
    void addatend(char);
    char delfrombeg();
    void print(node *);
};

struct node
{
    node *prev, *next;
    char l;
};