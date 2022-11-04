#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ArgumentManager.h"

using namespace std;

int main(int argc, char *argv[]) {
  //   ArgumentManager am(argc, argv);
  //   ifstream input(am.get("input"));
  //   ofstream output(am.get("output"));

  ifstream input("input1.txt");
  ofstream output("output1.txt");

  vector<string> words;
  map<string, int> wordMap;

  string in = "";
  if (input.peek() != EOF) {
    while (getline(input, in)) {
      // Clean up blank spaces, \n and \r, and skip blank lines
      in.erase(remove(in.begin(), in.end(), '\n'), in.end());
      in.erase(remove(in.begin(), in.end(), '\r'), in.end());
      if (in.size() == 0) continue;

      // Split the input into a vector of strings, strings separated by spaces
      string toAdd;
      for (auto c : in) {
        if (c == ' ') {
          words.push_back(toAdd);
          toAdd = "";
        } else
          toAdd += c;
      }

      sort(words.begin(), words.end());

      for (auto w : words) {
        if(wordMap.find(w) == wordMap.end()) {
          wordMap.insert_or_assign(w, 1);
        } else {
          wordMap.insert_or_assign(w, wordMap.at(w) + 1);
        }
      }
      for(auto w : wordMap) {
        output << w.first << " " << w.second << endl;
      }
    }
  }
}