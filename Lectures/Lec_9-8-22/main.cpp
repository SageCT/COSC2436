#include <iostream>
#include <string>
#include "word.h"

using namespace std;

int main()
{
    word name;
    name.addatend('a');
    name.addatend('l');
    name.addatend('e');
    name.print();
    name.deletefrombeg();
    name.print();
    name.printR(name.gethead());
    return 0;
}