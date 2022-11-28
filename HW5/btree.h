#ifndef BTREE_H
#define BTREE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
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

  void printLevel(node *n, int level, ostream &out) {
    if (n == nullptr) return;
    if (level == 1) {
      int i = 0;
      while (n->keys[i] != -1) out << n->keys[i] << " ", i++;
    }

    else if (level > 1) {
      for (int i = 0; i < degree; i++) {
        if (n->childptr[i] != nullptr)
          printLevel(n->childptr[i], level - 1, out);
      }
    }
  }

  int getHeight(node *n, int level) {
    if (n == nullptr) return 0;

    if (n->leaf)
      return level;
    else {
      int max = 0;
      for (int i = 0; i < degree; i++) {
        if (n->childptr[i] != nullptr) {
          int height = getHeight(n->childptr[i], level + 1);
          if (height > max) max = height;
        }
      }
      return max;
    }
  }

 public:
  btree(int _degree) {
    root = nullptr;
    degree = _degree;
  }

  int getHeight() { return 1 + getHeight(root, 0); }

  void printLevel(int level, ostream &out) {
    if (getHeight() < level)
      out << "Empty";
    else
      printLevel(root, level, out);
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

  // Finds the next available spot to insert a key, if the key can be added to
  // the node
  int findInsertion(node *n, int data) {
    if (n == nullptr) return 0;
    for (int i = 0; i <= n->size; i++)
      if (data < n->keys[i] || n->keys[i] == -1) return i;
    return -1;
  }

  // Helper function to insert childptrs into the parent node when the slot is
  // not occupied by -1
  void validateChildren(node *parent, node *leftNode, node *rightNode,
                        int index, int midKey) {
    parent->keys.insert(parent->keys.begin() + index, midKey);
    parent->size++;
    parent->keys.erase(remove(parent->keys.begin(), parent->keys.end(), -1),
                       parent->keys.end());
    while (parent->keys.size() < degree) parent->keys.push_back(-1);

    leftNode->parentptr = parent;
    rightNode->parentptr = parent;

    if (parent->childptr.at(index) != leftNode)
      parent->childptr.insert(parent->childptr.begin() + index, leftNode);
    parent->childptr.insert(parent->childptr.begin() + index + 1, rightNode);

    parent->childptr.erase(
        remove(parent->childptr.begin(), parent->childptr.end(), nullptr),
        parent->childptr.end());
    while (parent->childptr.size() < degree + 1)
      parent->childptr.push_back(nullptr);
  }

  // Helper function to add the midKey to the parent and add the children to the
  // parent without affecting the parent's other children. (Does not check for
  // if the parent is full)
  void addChildptrToParent(node *parent, node *leftNode, node *rightNode,
                           int midKey) {
    // Insert the midKey into the parent at the correct position.
    int i;
    for (i = 0; i < degree - 1; i++)
      if (parent->keys.at(i) > midKey || parent->keys.at(i) == -1) break;

    // If the slot is empty in parent, insert
    if (parent->keys.at(i) == -1) parent->keys.at(i) = midKey, parent->size++;
    // If the slot is not empty, call validate children to insert the left and
    // right nodes
    else
      validateChildren(parent, leftNode, rightNode, i, midKey);

    if (parent == root) cout << "Added to root: " << parent->keys[i] << endl;
    // Insert the leftNode at the correct position based on the index that the
    // midKey was added
    parent->childptr.at(i) = leftNode;
    parent->childptr.at(i + 1) = rightNode;

    parent->leaf = false;

    if (parent->parentptr == nullptr) root = parent;

    leftNode->parentptr = parent;
    rightNode->parentptr = parent;
    if (leftNode->childptr[0] != nullptr) leftNode->leaf = false;
    if (rightNode->childptr[0] != nullptr) rightNode->leaf = false;
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
    else if (findInsertion(n, data) != -1) {
      node *temp = n;
      while (!temp->leaf && findInsertion(temp, data) != -1)
        temp = temp->childptr[findInsertion(temp, data)];

      addAtLeaf(temp->parentptr, temp, data);
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
        cout << "Root is now: ";
        printLevel(1, cout);
        cout << endl;
        root = temp;
      } else
        splitChild(parent, n);
    }
  }

  // n is a full child, split it into two children with parent as the new
  // parent node. Need to find out if n is a leaf or not, pass pointers
  // depending.
  void splitChild(node *parent, node *leftNode) {
    // Passed as left, so create right node
    node *rightNode = new node(degree);
    int mid = (degree - 1) / 2;

    int midKey = leftNode->keys[mid];

    // copy half of left node to right node
    for (int x = 0; x < leftNode->size - mid; x++) {
      rightNode->keys[x] = leftNode->keys[x + mid + 1];
      rightNode->size++;

      leftNode->keys[x + mid + 1] = -1;
      leftNode->size--;
    }

    // Remove midKey from leftNode
    leftNode->keys[mid] = -1;
    leftNode->size--;

    leftNode->parentptr = parent;
    rightNode->parentptr = parent;

    // If passed node (leftNode) is not a leaf, copy the pointers to rightNode
    if (!leftNode->leaf) {
      // If not a leaf, has children, using the middle index, transfer bigger
      // children to rightNode from leftNode
      int x = 0;
      for (int i = mid + 1; i < degree + 1; i++) {
        rightNode->childptr.at(x) = leftNode->childptr.at(i);
        rightNode->childptr.at(x++)->parentptr = rightNode;
        leftNode->childptr.at(i) = nullptr;
      }

      // copy half the pointer of the left node to the right node
      /* --------------------- Done Above --------------------- */

      // find the correct position to add the new array within the parent
      // childptr array, need to add middlekey first because we are using add
      // at leaf.

      if (parent == nullptr) {
        // Create a new parent
        parent = new node(degree);
        // Add leftNode and rightNode to parent
        parent->leaf = false;
        parent->childptr[0] = leftNode;
        parent->childptr[1] = rightNode;
        leftNode->parentptr = parent;
        rightNode->parentptr = parent;
        parent->parentptr = nullptr;
        root = parent;
      }

      // add the middle key to the parent and add the left and right nodes as
      // children
      addChildptrToParent(parent, leftNode, rightNode, midKey);

      // If the parent is full, split the parent
      if (parent->size == degree) splitChild(parent->parentptr, parent);

    }

    else if (leftNode->leaf) {
      // If passed node (leftNode) is a leaf, send the middle key to the
      // parent

      addChildptrToParent(parent, leftNode, rightNode, midKey);

      // If the parent is full, call splitChild on the parent
      if (parent->size == degree) splitChild(parent->parentptr, parent);
    }
  }
};

#endif