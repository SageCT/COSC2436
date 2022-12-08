#include <cmath>

using namespace std;

class hashtable
{
private:
    int size;
    int *table;

public:
    hashtable(int s)
    {
        size = s;
        table = new int[size];
        for (int i = 0; i < size; i++)
            table[i] = -1;
    }

    int hash(int key) { return key % size; }
    int hash2(int key) { return 1 + (key % (size - 1)); }

    void insertQuad(int v)
    {
        int i = 0;
        int index = hash(v);
        while (table[index] != -1)
        {
            index = (int)(index + pow(i, 2)) % size;
            i++;
        }
    }

    void insertLin(int v)
    {
        int i = 0;
        int index = hash(v);
        while (table[index] != -1)
        {
            index = (index + i) % size;
            i++;
        }
    }

    void insertDoub(int v)
    {
        int i = 0;
        int index = hash(v);
        while (table[index] != -1)
        {
            index = hash(v) + i * hash2(v);
            i++;
        }
    }
};