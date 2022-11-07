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

void addToQueue(string s) {
  if (digitHere(s)) {
    // Placing the priority in queue
    int pri = stoi(s.substr(s.length() - 2, 1));
    string cmd = s.substr(0, s.length() - (s.length() - s.find(']') - 1));
    q.push(cmd, pri);
  } else {
    if (s == "Preorder") {
    }

    else if (s == "Inorder") {
    }

    else if (s == "Postorder") {
    }
  }
}

void DECODE() {
  string s = q.pop();
  s = s.substr(s.find('[') + 1,
               (s.length() - s.find('[') - (s.length() - s.find(']'))) - 1);
  messages.push(s);
}

void REPLACE(char curC, char newC) {}

void ADD(char curC, char newC) {}

void REMOVE(char c) {}

void SWAP(char a, char b) {}

void DECODEMESSAGE() {
  string s;
  while (q.top() != "-1") {
    s = q.pop();
    if (s.find("DECODE") != string::npos) {
      addToQueue(s);
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

void addToBST(string s) {}

int main(int argc, char *argv[]) {
  //   ArgumentManager am(argc, argv);
  //   ifstream input(am.get("input"));
  //   ofstream output(am.get("output"));

  ifstream input("input1.txt");
  ofstream output("output1.txt");
  vector<string> cmds;

  string s = "";

  while (input.peek() != EOF) {
    getline(input, s);
    addToQueue(s);
  }
  DECODE();
}