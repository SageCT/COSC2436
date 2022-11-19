#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string mixedNumber(int a, int b) {
  int whole = a / b;
  int remainder = a % b;
  string answer =
      to_string(whole) + " " + to_string(remainder) + " / " + to_string(b);
  return answer;
}

int main() {
  int a, b;
  cin >> a >> b;
  while (a != 0 && b != 0) {
    cout << mixedNumber(a, b) << endl;
    cin >> a >> b;
  }

  return 0;
}