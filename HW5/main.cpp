#include <iostream>
using namespace std;

struct node {
  int *keys;
  node **childptr;
  bool leaf;
  int size;

  node(int degree) {
    keys = new int[degree];
    childptr = new node *[degree + 1];
    leaf = true;
    size = 0;

    for (int i = 0; i < degree; i++) {
      keys[i] = -1;
    }
    for (int i = 0; i < degree + 1; i++) {
      childptr[i] = nullptr;
    }
  }
};

class btree {
 private:
  node *root;
  int degree;

 public:
  btree(int _degree) {
    root = nullptr;
    degree = _degree;
  }

  void insert(int data) {
    if (root == nullptr) {
      root = new node(degree);
      root->keys[0] = data;
      root->size = 1;
    } else {
      addAtLeaf(nullptr, root, data);
    }
  }

  void addAtLeaf(node *parent, node *n, int data) {
    if (n->leaf) {
      int i = n->size;
      while (i != 0 && data < n->keys[i - 1]) {
        n->keys[i] = n->keys[i - 1];
        i--;
      }
      n->keys[i] = data;
      n->size++;
    } else {
      int i = 0;
      while (i < n->size && data > n->keys[i]) {
        i++;
      }
      addAtLeaf(n, n->childptr[i], data);
    }
    if (n->size == degree) {
      //   split(parent, n);
      if (n == root) {
        node *temp = new node(degree);
        temp->leaf = false;
        temp->childptr[0] = n;
        splitChild(temp, n);
        root = temp;
      } else {
        splitChild(parent, n);
      }
    }
  }

  void splitChild(node *parent, node *leftNode) {
    node *rightNode = new node(degree);
    int mid = (degree - 1) / 2;

    // Copy half of left node to right node

    // Copy haf the pointer of left node to right node

    // Find the correct position to add the new array

    // Add the middle key to the parent node
  }
};

int main() {
  btree tree(3);
  return 0;
}