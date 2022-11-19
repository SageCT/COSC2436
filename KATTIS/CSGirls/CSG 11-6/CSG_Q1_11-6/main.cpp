#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string in;
  cin >> in;
  int n = stoi(in);

  vector<string> names, fullN, result;
  vector<double> startT, otherT, originalT, totalT;
  int finaltime = 0;

  cout.precision(3);

  while (n > 0) {
    string s;
    string s2;
    cin >> s;
    s2 += s;
    names.push_back(s);
    cin >> s;
    s2 += s;

    startT.push_back(stod(s));
    s2 += " " + s;

    cin >> s;
    otherT.push_back(stod(s));
    s2 += " " + s;

    fullN.push_back(s2);
    n--;
  }

  originalT = otherT;
  sort(otherT.begin(), otherT.end());
  sort(startT.begin(), startT.end());

  auto s = find(fullN.begin(), fullN.end(), startT[1]);
  int index = s - fullN.begin();
  result.push_back(fullN[index]);

  return 0;
}