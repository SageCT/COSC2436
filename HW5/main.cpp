#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ArgumentManager.h"
#include "btree2.h"

using namespace std;

int main(int argc, char *argv[]) {
  // ArgumentManager am(argc, argv);
  // ifstream input(am.get("input"));
  // ifstream cmd(am.get("command"));
  // ofstream out(am.get("output"));

  ifstream input("test.txt");
  ifstream cmd("command1.txt");
  ofstream out("output1.txt");

  vector<int> keys;
  int degree, level;

  // Taking inputs from the input file
  while (input.peek() != EOF) {
    int i;
    input >> i;
    keys.push_back(i);
  }

  // Deleting duplicate values before inputting to BTree
  keys.erase(unique(keys.begin(), keys.end()), keys.end());

  string s = "";
  while (cmd.peek() != EOF) {
    getline(cmd, s);
    s.erase(remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(remove(s.begin(), s.end(), '\r'), s.end());
    if (s.size() == 0) continue;

    // Find degree for tree
    if (s.find("Degree=") != string::npos)
      degree = stoi(s.substr(s.find("=") + 1));

    // Find level to print out
    else if (s.find("Level ") != string::npos)
      level = stoi(s.substr(s.find(" ") + 1));
  }

  // btree b(degree);
  BTree b(degree);

  for (auto k : keys) b.insert(k);

  cout << "Height: " << level << endl;
  b.printLevel(level, cout);

  return 0;
}