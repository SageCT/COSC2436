#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node {
  int *keys;
  node **childptr;
  node *parentptr;
  bool leaf;
  int size;

  node(int degree) {
    keys = new int[degree];
    childptr = new node *[degree + 1];
    parentptr = nullptr;
    leaf = true;
    size = 0;

    for (int i = 0; i < degree; i++) keys[i] = -1;
    for (int i = 0; i < degree + 1; i++) childptr[i] = nullptr;
  }

  node(node *parent, int degree) {
    keys = new int[degree];
    childptr = new node *[degree + 1];
    parentptr = parent;
    leaf = true;
    size = 0;

    for (int i = 0; i < degree; i++) keys[i] = -1;
    for (int i = 0; i < degree + 1; i++) childptr[i] = nullptr;
  }

  friend class btree;
};

class btree {
 private:
  node *root;
  int degree;

  node *printLevel(node *n, int level, ostream &out) {
    if (n == nullptr) return nullptr;
    if (n->leaf && level == 1) {
      for (int i = 0; i < n->size; i++) {
        out << n->keys[i] << " ";
      }
    } else if (level > 1) {
      printLevel(n->childptr[0], level - 1, out);
      printLevel(n->childptr[n->size], level - 1, out);
    }
  }

  node *trimExtra(node *toTrim, node *toLeave) {
    if (toTrim == nullptr) return nullptr;
    for () }

 public:
  btree(int _degree) {
    root = nullptr;
    degree = _degree;
  }

  // Inserts a node into the B-tree, if root is NOT nullptr, adds at leaf
  void insert(int data) {
    if (root == nullptr) {
      root = new node(degree);
      root->keys[0] = data;
      root->size = 1;
    } else {
      addAtLeaf(nullptr, root, data);
    }
  }

  // Adds the new node into the tree at first available leaf,
  // if leaf is full uses splitChild to create a new array
  void addAtLeaf(node *parent, node *n, int data) {
    // If n is a leaf
    if (n->leaf) {
      int i = n->size;
      // Find the first spot where data is less than keys[i - 1]
      while (i != 0 && data < n->keys[i - 1]) {
        // Pointer of arrays can change size dynamically
        n->keys[i] = n->keys[i - 1];
        i--;
      }
      // Add data to the node where data is greater than array at index
      n->keys[i] = data;
      n->parentptr = parent;
      n->size++;
    }

    // Else find the first index where the data is bigger that keys[i] and
    // call addAtLeaf() again to add it to traverse the tree and add it to a
    // leaf
    else {
      int i = 0;
      while (i < n->size && data > n->keys[i]) {
        i++;
      }
      addAtLeaf(n, n->childptr[i], data);
    }

    // Need to determine if node is a leaf within splitChild() if it is, then
    // split node accordingly
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

  // n is a full child, split it into two children with parent as the new
  // parent node. Need to find out if n is a leaf or not, pass pointers
  // depending.
  void splitChild(node *parent, node *leftNode) {
    // Passed as left, so create right node
    node *rightNode = new node(degree);
    int mid = (degree - 1) / 2;
    rightNode->size = degree - mid - 1;

    int midKey = leftNode->keys[mid];

    // copy half of left node to right node
    for (int x = 0; x < rightNode->size - 1; x++) {
      rightNode->keys[x] = leftNode->keys[x + mid + 1];
      leftNode->keys[x + mid + 1] = -1;
      leftNode->size--;
    }
    // If passed node (leftNode) is not a leaf, copy the pointers to rightNode
    if (!leftNode->leaf) {
      // For each child in passed node, check the children's key values to see
      // if it belongs in left or right node
      vector<node *> leftptr;
      int i = 0;
      for (int x = 0; x < degree; x++) {
        int biggestChildKey = -1;
        if (leftNode->childptr[x] != nullptr) {
          for (int y = leftNode->childptr[x]->size - 1; y >= 0; y--) {
            biggestChildKey = leftNode->childptr[x]->keys[y];
            // If biggestkey > midkey, then it belongs in the right node also
            // delete that pointer from the left node
            if (biggestChildKey > midKey && biggestChildKey > -1) {
              rightNode->childptr[i++] = leftNode->childptr[x];
              leftNode->childptr[x] = nullptr;
              break;
            }
          }
        }
      }
    }
    // copy half the pointer of the left node to the right node
    /* --------------------- Done Above --------------------- */

    // find the correct position to add the new array

    // add the middle keys to the parent
    for (int i = parent->size - 1; i >= 0; i--) {
      if (parent->keys[i] < midKey && parent->keys[i + 1] < degree - 1) {
        parent->keys[i + 1] = midKey;
      }
    }

    // // vector<int> childkeys;
    // // int highest = -1;
    // // for (int y = 0; y < degree; y++) {
    // //   int highestVal = -1;
    // //   if (leftNode->childptr[x]->keys[y] != -1) {
    // //     childkeys.push_back(leftNode->childptr[x]->keys[y]);
    // //   }
    // // }
    // // After adding all the keys of a child to the vector, sort to find
    // // the largest value
    // sort(childkeys.begin(), childkeys.end(), greater<int>());
    // highest = childkeys[0];

    // // If the highest value is greater than the midKey (which will be
    // // passed to the parent), then it belongs in the right node
    // if (highest > midKey) {
    //   rightNode->childptr[i] = leftNode->childptr[x];
    // } else if (highest < midKey && highest != -1) {
    //   leftptr.push_back(leftNode->childptr[x]);
    // }
  }

  void printLevel(int level, ostream &out) { printLevel(root, level, out); }
};

#endif