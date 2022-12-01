#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "ArgumentManager.h"
using namespace std;

struct item {
  string name;
  double priority;
};

class priQueue {
 private:
  int size;
  vector<item> tasks;

 public:
  priQueue() { size = 0; }
  ~priQueue() {}
  void push(string, double);
  string pop();
  string top() const {
    if (!isEmpty()) return tasks[0].name;
    return "-1";
  };
  int getSize() const { return size; }
  bool isEmpty() const { return size == 0; }
};

void priQueue::push(string task, double pri) {
  item toAdd = {task, pri};
  if (isEmpty()) {
    tasks.push_back(toAdd);
    size++;
  } else {
    int index = size - 1;
    while (index > -1) {
      if (index == 0 && pri < tasks[index].priority) {
        tasks.insert(tasks.begin() + index, toAdd);
        index--, size++;
      } else if ((double)pri < (double)tasks[index].priority) {
        index--;
      } else if ((double)pri >= (double)tasks[index].priority) {
        tasks.insert(tasks.begin() + index + 1, toAdd);
        index = -1;
        size++;
      }
    }
  }
}

string priQueue::pop() {
  if (!isEmpty()) {
    string temp = tasks[0].name;
    tasks.erase(tasks.begin() + 0);
    size--;
    return temp;
  }
  return "-1";
}

int digitHere(string s) {
  for (int i = 0; i < s.length(); i++)
    if (isdigit(s[i])) return i;
  return -1;
}

int main(int argc, char *argv[]) {
  //   ArgumentManager am(argc, argv);
  //   ifstream input(am.get("input"));
  //   ofstream output(am.get("output"));

  ifstream input("input3.txt");
  ofstream output("output1.txt");

  string in = "";
  if (input.peek() != EOF) {
    priQueue tasks;
    string task = "";
    double priority = 0;

    while (getline(input, in)) {
      // Clean up blank spaces, \n and \r, and skip blank lines
      in.erase(remove(in.begin(), in.end(), '\n'), in.end());
      in.erase(remove(in.begin(), in.end(), '\r'), in.end());
      if (in.size() == 0) continue;
      // If there is a digit in the string, find the task and priority
      if (digitHere(in) != -1) {
        task = in.substr(0, digitHere(in) - 1);
        priority = stod(in.substr(digitHere(in), in.length() - digitHere(in)));
        tasks.push(task, priority);
      }
    }
    // Outputs the priority queue using pop() and top()
    while (tasks.top() != "-1") {
      output << tasks.pop();
      if (tasks.top() != "-1") output << endl;
    }
    tasks.pop();
  }
}