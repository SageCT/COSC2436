#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int jack3(int a, int b, int c) { return a * b * c; }

int main() {
  int a, b, c;
  cin >> a >> b >> c;
  cout << jack3(a, b, c);

  return 0;
}