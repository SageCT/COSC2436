#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ArgumentManager.h"
#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
  // ArgumentManager am(argc, argv);
  // ifstream input(am.get("input"));
  // ifstream cmd(am.get("command"));
  // ofstream out(am.get("output"));

  ifstream input("input2.txt");
  ifstream cmd("command2.txt");
  ofstream out("output1.txt");

  vector<int> keys, levels;

  int degree;

  // Taking inputs from the input file
  while (input.peek() != EOF) {
    int i;
    input >> i;
    if (find(keys.begin(), keys.end(), i) == keys.end()) keys.push_back(i);
  }

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
      levels.push_back(stoi(s.substr(s.find(" ") + 1)));
  }

  // btree b(degree);
  btree b(degree);

  for (auto k : keys) b.insert(k);

  out << "Height=" << b.getHeight() << endl;

  for (auto l : levels) {
    b.printLevel(l, out);
    out << endl;
  }

  return 0;
}