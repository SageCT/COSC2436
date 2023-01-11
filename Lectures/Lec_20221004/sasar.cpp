#include "sasar.h"

template <class T>
bool sasar<T>::pop(T &k)
{
    if (!isempty())
    {
        k = elt[top];
        top--;
        return true;
    }
    return false;
}