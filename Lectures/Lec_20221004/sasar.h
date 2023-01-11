template <class T>
class sasar
{
private:
    int *elt;
    int size;
    int top;

public:
    sasar(int = 10);
    bool isfull();
    bool isempty();
    bool push(T);   // call isfull... bool return true if possible to push
    bool pop(T &k); // call isempty
    void print();
};