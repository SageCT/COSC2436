#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void reverse(string &s) {
  for (int i = 0; i < s.length() / 2; i++) {
    char temp = s[i];
    s[i] = s[s.length() - 1 - i];
    s[s.length() - 1 - i] = temp;
  }
}

int main() {
  int n;
  vector<string> s, r;
  string temp;
  cin >> n;

  for (int x = 0; x < n; x++) {
    int rows = 0, cols = 0, i = 0;
    cin >> rows >> cols;

    for (int i = 0; i < rows; i++) {
      temp = "";
      cin >> temp;
      s.push_back(temp);
    }

    
    for (int j = rows - 1; j >= 0; j--) {
      temp = "";
      temp = s[j];
      reverse(temp);
      r.push_back(temp);
    }

    // Couting the flipped image
    cout << "Test " << x + 1 << endl;
    for (auto c : r) cout << c << endl;

    r.clear(), s.clear();
  }
  return 0;
}