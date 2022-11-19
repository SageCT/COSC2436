#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void removeDupes(vector<int> &v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

int main() {
  vector<int> v;
  int e, d1, d2;
  int answer;

  cin >> e;
  while (e > 0) {
    cin >> d1 >> d2;
    for (int i = d1; i < d2 + 1; i++) v.push_back(i);
    e--;
  }

  removeDupes(v);

  answer = v.size();
  answer >= 365 ? cout << 365 : cout << answer;

  return 0;
}