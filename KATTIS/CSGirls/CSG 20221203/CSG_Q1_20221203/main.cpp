// #include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;
typedef long long ll;

int main() {
  int h;
  string path;
  cin >> h >> path;

  int cur = 1;
  for (char c : path) cur = cur * 2 + (c == 'R');

  cout << (1 << (h + 1)) - cur << endl;
  return 0;
}