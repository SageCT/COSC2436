#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Passes all test cases!
int main() {
  int n, t;
  int temp, counter(0);
  cin >> n >> t;
  queue<int> q;

  while (n > 0) {
    cin >> temp;
    q.push(temp);
    n--;
  }
  while (t - q.front() >= 0 && !q.empty()) {
    t -= q.front();
    q.pop();
    counter++;
  }

  cout << counter;
  return 0;
}