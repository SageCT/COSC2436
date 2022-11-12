#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ArgumentManager.h"
#include "Tree.h"

using namespace std;

int main(int argc, char *argv[]) {
  //   ArgumentManager am(argc, argv);
  //   ifstream input(am.get("input"));
  //   ofstream output(am.get("output"));

  ifstream input("input1.txt");
  ofstream output("output1.txt");

  Tree t;
  while (input.peek() != EOF) {
    int x;
    input >> x;
    cout << x << " ";
    t.insert(t.getRoot(), x);
  }

  t.print(t.getRoot(), std::cout);
}