struct letter
{
    char l;
    letter *next;
};

class word
{
private:
    letter *head;
    letter *tail;

public:
    word() { head = tail = 0; }
    void addatend(char);
    void deletefrombeg();
    void print();
    void printR(letter *);
    letter *gethead();
    bool search(char);
};
