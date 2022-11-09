#include <iostream>

using namespace std;

struct node {
  int val;
  node *left;
  node *right;
};

void inorder(node *cu) {
  if (cu != nullptr) {
    inorder(cu->left);
    cout << cu->val;
    inorder(cu->right);
  }
}

bool search(node *cu, int key) {
  if (cu != nullptr) {
    inorder(cu->left);
    if (cu->val == key) {
      return true;
    }
    inorder(cu->right);
  }
  return false;
}

int main() { return 0; }