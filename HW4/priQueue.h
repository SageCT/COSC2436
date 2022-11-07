#ifndef PRIQUEUE_H
#define PRIQUEUE_H
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct item {
  string cmd;
  int priority;
};

class priQueue {
 private:
  int size;
  vector<item> cmds;

 public:
  priQueue() { size = 0; }
  ~priQueue() {}
  void push(string, int);
  string pop();
  string top() const {
    if (!isEmpty()) return cmds[0].cmd;
    return "-1";
  };
  int getSize() const { return size; }
  bool isEmpty() const { return size == 0; }
};

void priQueue::push(string cmd, int pri) {
  item toAdd = {cmd, pri};
  if (isEmpty()) {
    cmds.push_back(toAdd);
    size++;
  } else {
    int index = size - 1;
    while (index > -1) {
      if (index == 0 && pri < cmds[index].priority) {
        cmds.insert(cmds.begin() + index, toAdd);
        index--, size++;
      } else if (pri < cmds[index].priority) {
        index--;
      } else if (pri >= cmds[index].priority) {
        cmds.insert(cmds.begin() + index + 1, toAdd);
        index = -1;
        size++;
      }
    }
  }
}

string priQueue::pop() {
  if (!isEmpty()) {
    string temp = cmds[0].cmd;
    cmds.erase(cmds.begin() + 0);
    size--;
    return temp;
  }
  return "-1";
}

#endif