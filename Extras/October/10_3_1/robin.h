#ifndef ROBIN_H
#define ROBIN_H

#include <iostream>
#include <string>

using namespace std;

struct node {
  string job;
  int totalMin;
  int remainMin;
  node *next;
};

class robin {
 private:
  node *front;
  node *back;

 public:
  robin();
  ~robin();
  bool isEmpty() const { return (front == nullptr); }
  void enq(string, int, int);
  void enq(node *n);
  node *deq();
  void roundR(int &);
  void deqDel();
  void print();
};

robin::robin() { front = back = nullptr; }

robin::~robin() {
  while (front != nullptr) {
    node *temp = front->next;
    delete front;
    front = temp;
  }
}

void robin::enq(string st, int a, int b) {
  node *temp = new node();
  temp->job = st, temp->totalMin = a, temp->remainMin = b, temp->next = nullptr;

  if (isEmpty()) {
    front = temp;
    back = temp;
    front->next = back;
  } else {
    back->next = temp;
    back = temp;
  }
}

void robin::enq(node *n) {
  node *temp = new node();
  temp->job = n->job;
  temp->remainMin = n->remainMin;
  temp->totalMin = n->totalMin;
  temp->next = nullptr;

  if (isEmpty()) {
    front = temp;
    back = temp;
    front->next = back;
  } else {
    back->next = temp;
    back = temp;
  }
}

node *robin::deq() {
  if (front != nullptr) {
    node *temp = front;
    front = front->next;

    return temp;
  }

  return nullptr;
}

// Performs round robin function, moves front to next front, then enqueues the
// front to the back of the queue. Keeps looping until time is 0.
void robin::roundR(int &remTime) {
  string origJob = front->job;
  while (remTime - front->totalMin > 0) {
    front->remainMin = remTime;
    remTime -= front->totalMin;
    front->remainMin = remTime;

    cout << front->job << " Completed " << remTime << " remaining time."
         << endl;

    node *temp = front;
    front = front->next;
    enq(temp);

    if (origJob == front->job) cout << "Looping with excess time\n" << endl;
  }

  cout << "No time remaining." << endl;
}

void robin::deqDel() {
  if (front != nullptr) {
    node *temp = front;
    front = front->next;

    delete temp;
  }
}

void robin::print() {
  robin saveQ;
  while (front != nullptr) {
    cout << "Job Name: " << front->job << " Job Remaining Time "
         << front->remainMin << " Job Total Time " << front->totalMin << endl;
    saveQ.enq(deq());
  }

  cout << "\n";

  while (saveQ.front != nullptr) {
    enq(saveQ.front);
    saveQ.deqDel();
  }
}

#endif