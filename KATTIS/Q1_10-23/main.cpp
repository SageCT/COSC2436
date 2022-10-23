#include <iostream>
#include <queue>

#include "heap.h"

using namespace std;

priority_queue<int> oof;

int getMax() { return oof.top(); }

int getSize() { return oof.size(); }

void insert(int n) { oof.push(n); }

void removeMax() { oof.pop(); }
