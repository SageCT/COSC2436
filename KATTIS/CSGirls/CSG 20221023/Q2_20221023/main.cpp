#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(vector<string> &names, int x, int y) {
  string temp = names[x];
  names[x] = names[y];
  names[y] = temp;
}

int main() {
  vector<string> names;
  int num;
  string temp;
  cin >> num;

  while (num > 0) {
    names.clear();
    string temp = "";

    for (int x = 0; x < num; x++) {
      cin >> temp;
      names.push_back(temp);
    }

    // Sorting names based off the first 2 letters
    for (int x = 0; x < names.size() - 1; x++)
      for (int y = 0; y < names.size() - x - 1; y++)
        if (names[y].substr(0, 2) > (names[y + 1].substr(0, 2)))
          swap(names, y, y + 1);

    for (int x = 0; x < num; x++) cout << names[x] << endl;
    cout << endl;

    cin >> num;
  }
}