#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "ArgumentManager.h"

using namespace std;
class BST {
  int data;
  BST *left, *right;

 public:
  BST();
  BST(int);

  BST* Insert(BST*, int);

  void Preorder(BST*, ofstream&, int&, string);
};

// Default Constructor definition.
BST::BST() : data(0), left(NULL), right(NULL) {}

BST::BST(int value) {
  data = value;
  left = right = NULL;
}

BST* BST::Insert(BST* root, int value) {
  if (!root) {
    return new BST(value);
  }

  if (value > root->data) {
    root->right = Insert(root->right, value);
  } else if (value < root->data) {
    root->left = Insert(root->left, value);
  }

  return root;
}

void BST::Preorder(BST* node, ofstream& fileName, int& value, string order) {
  if (node == NULL) return;

  if (value == 0) {
    cout << order << "] " << node->data;
    fileName << order << "] " << node->data;
    value++;
  } else {
    fileName << "\n" << order << "] " << node->data;
    cout << "\n" << order << "] " << node->data;
  }

  Preorder(node->left, fileName, value, order += "l");
  order = order.substr(0, order.length() - 1);
  Preorder(node->right, fileName, value, order += "r");
}

int main(int argc, char* argv[]) {
  // *** You need to open files using argumentmanager when submit your
  // assignment ***
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to
  // change back to using argumentmanager when you submit the assignment ***
  BST b, *root = NULL;
  // ifstream input("input3.txt");
  // ofstream out("output1.txt");
  if (!input.is_open()) {
    exit(-1);
  }

  string in = "", number = "";

  while (getline(input, in)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    in += " ";
    for (int i = 0; i < in.length(); i++) {
      if (in[i] == ' ') {
        int num = stoi(number);
        root = b.Insert(root, num);
        number = "";
      } else {
        number += in[i];
      }
    }
  }

  int zero = 0;
  string order = "[x";
  b.Preorder(root, out, zero, order);
}