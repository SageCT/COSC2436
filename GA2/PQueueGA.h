#ifndef PQUEUEGA_H
#define PQUEUEGA_H
#include <iostream>
#include <vector>
using namespace std;

struct node {
	string eq;
	float ans;
	node* next;
};

class PQueueGA {
private:
	node* front;
public:
	PQueueGA() { front = nullptr; }
	void enq(node* temp) {
		temp->next = nullptr;
		PQueueGA q;
		node* curr = front;
		if (front == nullptr) {
			front = temp;
		}
		else if (front->ans > temp->ans) {
			temp->next = front;
			front = temp;
		}
		else {
			while (curr->next != nullptr && curr->next->ans <= temp->ans) {
				curr = curr->next;
			}
			temp->next = curr->next;
			curr->next = temp;
		}
	}
	node* deq() {
		node* temp = front;
		front = front->next;
		return temp;
	}
	bool empty() {
		return (front == nullptr);
	}
};

#endif