#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n, city;
  string in;
  set<string> s;

  cin >> n;
  while (n > 0) {
    cin >> city;
    while (city > 0) {
      cin >> in;
      s.insert(in);
      city--;
    }
    cout << s.size() << endl;
    s.clear();
    n--;
  }

  return 0;
}