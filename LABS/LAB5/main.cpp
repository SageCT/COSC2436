#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ArgumentManager.h"

using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  // ifstream input("input3.txt");
  // ofstream output("output1.txt");

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
        if (c == ' ' || c == '.' || c == ',' || c == '!' || c == '?') {
          if (!toAdd.empty()) words.push_back(toAdd);
          toAdd = "";
        } else if (c != '"')
          toAdd.push_back(tolower(c));
      }
    }

    for (auto w : words) {
      if (wordMap.find(w) == wordMap.end()) {
        wordMap.insert(pair<string, int>(w, 1));
      } else {
        int num = wordMap[w] + 1;
        wordMap.erase(w);
        wordMap.insert(pair<string, int>(w, num));
      }
    }
    for (auto itr = wordMap.begin(); itr != wordMap.end(); itr++) {
      itr == --wordMap.end()
          ? output << itr->first << ": " << itr->second
          : output << itr->first << ": " << itr->second << endl;
    }
  }
}
