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
queue<string> messages;

bool digitHere(string s) {
  for (int i = 0; i < s.length(); i++)
    if (isdigit(s[i])) return true;
  return false;
}

void addToQueue(string s, BST &b) {
  if (digitHere(s)) {
    // Placing the priority in queue

    // Finding the priority
    int pri = stoi(s.substr(s.length() - 2, 1));
    // finding the command
    string cmd = s.substr(0, s.length() - (s.length() - s.find(']') - 1));
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
  messages.push(s);
}

void REPLACE(char curC, char newC) {
  string s = messages.front();
  messages.pop();
  for (int i = 0; i < s.length(); i++)
    if (s[i] == curC) s[i] = newC;
  messages.push(s);
}

void ADD(char curC, char newC) {
  string s = messages.front();
  messages.pop();
  for (int i = 0; i < s.length(); i++)
    if (s[i] == curC) s.insert(i + 1, 1, newC);
  messages.push(s);
}

void REMOVE(char c) {
  string s = messages.front();
  messages.pop();
  for (int i = 0; i < s.length(); i++)
    if (s[i] == c) s.erase(i, 1);
  messages.push(s);
}

void SWAP(char a, char b) {
  string s = messages.front();
  messages.pop();
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == a)
      s[i] = b;
    else if (s[i] == b)
      s[i] = a;
  }
  messages.push(s);
}

void DECODEMESSAGES() {
  string s;
  while (q.top() != "-1") {
    s = q.pop();
    if (s.find("DECODE") != string::npos) {
      DECODE();
    } else if (s.find("REPLACE") != string::npos)
      REPLACE(s[10], s[12]);
    else if (s.find("ADD") != string::npos)
      ADD(s[5], s[7]);
    else if (s.find("REMOVE") != string::npos)
      REMOVE(s[8]);
    else if (s.find("SWAP") != string::npos)
      SWAP(s[6], s[8]);
  }
}

void addToBST(string s, BST &b) {}

int main(int argc, char *argv[]) {
  //   ArgumentManager am(argc, argv);
  //   ifstream input(am.get("input"));
  //   ofstream output(am.get("output"));

  ifstream input("input1.txt");
  ofstream output("output1.txt");

  string s = "";
  BST bst;

  while (input.peek() != EOF) {
    getline(input, s);
    addToQueue(s, bst);
  }
  DECODEMESSAGES();

  while (!messages.empty()) {
    addToBST(messages.front(), bst);
    messages.pop();
  }
}