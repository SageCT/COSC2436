#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ArgumentManager.h"
#include "Tree.h"

using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  // ifstream input("input3.txt");
  // ofstream output("output1.txt");

  Tree t;
  int x;
  input >> x;
  x = 0;
  while (input.peek() != EOF) {
    input >> x;

    t.insert(t.getRoot(), x);
  }

  t.print(t.getRoot(), output);
}
