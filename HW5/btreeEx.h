// A C++ program to perform insertion on btree

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

// A class to create a node

class btreenode {
  int *key;
  int t;
  btreenode **c;  // A child pointers array
  int n;
  bool leaf;  // returns true if tree is empty

 public:
  btreenode(int _t, bool _leaf);  // btreenode class constructor

  // A function to insert a new key in the subtree rooted with non full node.
  void insertnonfull(int k);

  // A function to split the child y of this node.
  void splitchild(int i, btreenode *y);

  // A function to traverse the b-tree
  void traverse();

  // A function to search the key in the b-tree

  btreenode *search(int k);  // if k not found the returns NULL

  // we will make btree friend of btreenode class so that we can access private
  // members of this class

  friend class btree;
};

// class btree

class btree

{
  btreenode *root;  // root node pointer
  int t;

 public:
  // btree class Constructor initialized as empty
  btree(int _t) {
    root = NULL;

    t = _t;
  }

  // function to traverse the tree
  void traverse() {
    if (root != NULL) root->traverse();
  }

  // A function to insert the key in the node

  void insert(int k);
};

// btreenode class constructor

btreenode::btreenode(int t1, bool leaf1)

{
  t = t1;
  leaf = leaf1;

  // Allocate memory for max possible keys
  // and the child pointers
  key = new int[2 * t - 1];
  c = new btreenode *[2 * t];

  n = 0;
}

// A function to traverse the tree

void btreenode::traverse()

{
  int i;
  for (i = 0; i < n; i++)
  {
    if (leaf == false) c[i]->traverse();
    cout << " " << key[i];
  }

  if (leaf == false) c[i]->traverse();
}

// A Function to insert a key in B-Tree

void btree::insert(int k)

{
  // check if tree is empty

  if (root == NULL)

  {
    root = new btreenode(t, true);

    root->key[0] = k;

    root->n = 1;

  }

  else

  {
    // If root is full, then tree's height increases

    if (root->n == 2 * t - 1)

    {
      btreenode *s = new btreenode(t, false);

      // Change old root as new root's child

      s->c[0] = root;

      s->splitchild(0, root);

      int i = 0;

      if (s->key[0] < k) i++;

      s->c[i]->insertnonfull(k);

      root = s;

    }

    else  // If root is empty,then we will call insertnonfull

      root->insertnonfull(k);
  }
}

void btreenode::insertnonfull(int k)

{
  // Initialize index as rightmost element's index

  int i = n - 1;

  if (leaf == true)

  {
    // The following loop will find the location of key

    // and move all bigger keys one place further

    while (i >= 0 && key[i] > k)

    {
      key[i + 1] = key[i];

      i--;
    }

    key[i + 1] = k;

    n = n + 1;

  }

  else  // If this node is not the leaf

  {
    while (i >= 0 && key[i] > k) i--;

    if (c[i + 1]->n == 2 * t - 1)

    {
      splitchild(i + 1, c[i + 1]);

      if (key[i + 1] < k) i++;
    }

    c[i + 1]->insertnonfull(k);
  }
}

void btreenode::splitchild(int i, btreenode *y)

{
  //

  btreenode *z = new btreenode(y->t, y->leaf);

  z->n = t - 1;

  for (int j = 0; j < t - 1; j++) z->key[j] = y->key[j + t];

  if (y->leaf == false)

  {
    for (int j = 0; j < t; j++) z->c[j] = y->c[j + t];
  }

  y->n = t - 1;

  for (int j = n; j >= i + 1; j--) c[j + 1] = c[j];

  c[i + 1] = z;

  for (int j = n - 1; j >= i; j--) key[j + 1] = key[j];

  key[i] = y->key[t - 1];

  // we will increment count of keys

  n = n + 1;
}

int main()

{
  btree p(3);  // A B-Tree with minium degree 3

  p.insert(15);

  p.insert(2);

  p.insert(25);

  p.insert(16);

  p.insert(32);

  p.insert(30);

  p.insert(6);

  p.insert(7);

  cout << "Traversal of the constructed tree is ";

  p.traverse();

  return 0;
}