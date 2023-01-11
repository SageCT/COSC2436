#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int main() {
  double n;
  cin >> n;
  int ans = ((double)5280 / (double)4854) * ((double)1000 * n) + 0.5;
  cout << ans << endl;
  return 0;
}