#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node {
  vector<int> keys;
  vector<node *> childptr;
  node *parentptr;
  bool leaf;
  int size;

  node(int degree) {
    // Keys is of size degree
    keys.resize(degree);
    // Childptr is of size degree + 1
    childptr.resize(degree + 1);
    parentptr = nullptr;
    leaf = true;
    size = 0;

    for (int i = 0; i < degree; i++) keys[i] = -1;
    for (int i = 0; i < degree + 1; i++) childptr[i] = nullptr;
  }

  node(node *parent, int degree) {
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

  void printChildptr(node *n, ostream &out) {
    for (int i = 0; i < degree; i++) {
      if (n->childptr[i] != nullptr)
        for (int x = 0; x < n->childptr[i]->keys.size(); x++) {
          if (n->childptr[i]->keys[x] != -1)
            out << n->childptr[i]->keys[x] << " ";
          else {
            break;
          }
        }
    }
  }

  void printLevel(node *n, int level, ostream &out) {
    if (n == nullptr) return;
    if (level == 1) {
      int i = 0;
      while (n->keys[i] != -1) cout << n->keys[i] << " ", i++;
    }

    else if (level > 1) {
      for (int i = 0; i < degree; i++) {
        if (n->childptr[i] != nullptr)
          printLevel(n->childptr[i], level - 1, out);
      }
    }
  }

 public:
  btree(int _degree) {
    root = nullptr;
    degree = _degree;
  }

  // Inserts a node into the B-tree, if root is NOT nullptr, adds at leaf
  void insert(int data) {
    if (root == nullptr) {
      cout << "Root is nullptr adding : " << data << endl;
      root = new node(degree);
      root->keys[0] = data;
      root->size = 1;
    } else {
      cout << "Adding, root not empty: " << data << endl;
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
      cout << "Adding " << data << " to index " << i << endl;
      n->keys[i] = data;
      n->parentptr = parent;
      n->size++;
    }

    // Else find the first index where the data is bigger that keys[i] and
    // call addAtLeaf() again to add it to traverse the tree and add it to a
    // leaf
    else {
      int i = 0;
      while (i < n->size - 1 && data > n->keys[i]) {
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
        temp->size = 0;
        splitChild(temp, n);
        cout << "Root is now: " << temp->keys[0] << endl;
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
    for (int x = 0; x <= rightNode->size - 1; x++) {
      rightNode->keys[x] = leftNode->keys[x + mid + 1];

      leftNode->keys[x + mid + 1] = -1;
      leftNode->size--;
    }

    // Remove midKey from leftNode
    leftNode->keys[mid] = -1;
    leftNode->size--;

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

      // copy half the pointer of the left node to the right node
      /* --------------------- Done Above --------------------- */

      // find the correct position to add the new array within the parent
      // childptr array, need to add middlekey first because we are using add at
      // leaf.

      // add the middle key to the parent
      for (int i = parent->size - 1; i >= 0; i--) {
        if (parent->keys[i] < midKey && parent->size < degree - 1) {
          parent->keys[i + 1] = midKey;
          break;
        }
      }

      // Add the keys from the left and right nodes to the parent through
      // addAtLeaf
      for (int i = 0; i < degree; i++) {
        if (leftNode->childptr[i] != nullptr) {
          for (int x = 0; x < degree; x++)
            if (leftNode->childptr[i]->keys[x] > -1) {
              addAtLeaf(parent->parentptr, parent,
                        leftNode->childptr[i]->keys[x]);
            }
        }
      }
    }

    else if (leftNode->leaf) {
      // If passed node (leftNode) is a leaf, send the middle key to the parent
      int i = parent->size;
      // Find the first spot where data is less than keys[i - 1]
      while (i != 0 && midKey < parent->keys[i - 1]) {
        // Pointer of arrays can change size dynamically
        parent->keys[i] = parent->keys[i - 1];
        i--;
      }

      parent->keys[i] = midKey;
      parent->size++;

      int j = degree;
      while (parent->childptr[j] == nullptr && j != 0) {
        j--;
      }

      parent->childptr[j + 1] = rightNode;
    }

    for (int i = 0; i < degree; i++) {
      if (rightNode->childptr[i] != nullptr) {
        for (int x = 0; x < degree; x++)
          if (rightNode->childptr[i]->keys[x] > -1) {
            addAtLeaf(parent->parentptr, parent,
                      rightNode->childptr[i]->keys[x]);
          }
      }
    }
  }

  void printLevel(int level, ostream &out) { printLevel(root, level, out); }
};

#endif