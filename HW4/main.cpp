#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "ArgumentManager.h"
#include "BST.h"
#include "priQueue.h"

using namespace std;

priQueue q;
queue<string> msgs;

bool digitHere(string s) {
  for (int i = 0; i < s.length(); i++)
    if (isdigit(s[i])) return true;
  return false;
}

void addToBST(string s, BST &b) { b.insert(s); }

void addToQueue(string s, BST &b) {
  if (digitHere(s)) {
    // Placing the priority in queue

    // Finding the priority
    int pri = stoi(s.substr(s.length() - 2, 1));
    // finding the command
    string cmd = s.substr(0, s.length() - (s.length() - s.find(']') - 1));
    cout << "Adding cmd: " << cmd << " with priority: " << pri << endl;
    q.push(cmd, pri);
  } else {
    // Set the BST traversal mode
    b.setMode(s);
  }
}

void DECODE() {
  string s = q.pop();
  s = s.substr(s.find('[') + 1,
               (s.length() - s.find('[') - (s.length() - s.find(']'))) - 1);
  msgs.push(s);
}

void REPLACE(char curC, char newC) {
  string s = msgs.front();
  msgs.pop();
  for (int i = 0; i < s.length(); i++)
    if (s[i] == curC) s[i] = newC;
  msgs.push(s);
}

void ADD(char curC, char newC) {
  string s = msgs.front();
  msgs.pop();
  for (int i = 0; i < s.length(); i++)
    if (s[i] == curC) s.insert(i + 1, 1, newC);
  msgs.push(s);
}

void REMOVE(char c) {
  string s = msgs.front();
  msgs.pop();
  for (int i = 0; i < s.length(); i++)
    if (s[i] == c) s.erase(i, 1);
  msgs.push(s);
}

void SWAP(char a, char b) {
  string s = msgs.front();
  msgs.pop();
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == a)
      s[i] = b;
    else if (s[i] == b)
      s[i] = a;
  }
  msgs.push(s);
}

void DECODEMESSAGES(BST &b, ofstream &o) {
  string s;
  while (q.top() != "-1") {
    s = q.pop();

    if (s.find("DECODE") != string::npos) {
      DECODE();
      cout << "DECODE: " << s << endl;
    } else if (s.find("REPLACE") != string::npos) {
      cout << "REPLACE: " << s[9] << s[11] << endl;
      REPLACE(s[9], s[11]);
    } else if (s.find("ADD") != string::npos) {
      cout << "ADD: " << s[5] << s[7] << endl;
      ADD(s[5], s[7]);
    } else if (s.find("REMOVE") != string::npos) {
      cout << "REMOVE: " << s[8] << endl;
      REMOVE(s[8]);

    } else if (s.find("SWAP") != string::npos) {
      cout << "SWAP: " << s[6] << s[8] << endl;
      SWAP(s[6], s[8]);
    } else if (s.find("BST") != string::npos) {
      cout << "ADDING TO BST: " << s << endl;
      addToBST(msgs.front(), b);
      msgs.pop();
    } else if (s == "Inorder" || s == "Preorder" || s == "Postorder") {
      if (s == "Inorder")
        b.inOrderTrav(o);
      else if (s == "Preorder")
        b.preOrderTrav(o);
      else
        b.postOrderTrav(o);
    }
  }
}

int main(int argc, char *argv[]) {
  //   ArgumentManager am(argc, argv);
  //   ifstream input(am.get("input"));
  //   ofstream output(am.get("output"));

  ifstream input("input1.txt");
  ofstream output("output1.txt");

  string s = "";
  BST tree;

  while (input.peek() != EOF) {
    getline(input, s);
    addToQueue(s, tree);
  }
  DECODEMESSAGES(tree, output);
}