#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void factorial(int fact[], int n) {
  fact[0] = 1;
  for (long long int i = 1; i < n; i++) fact[i] = fact[i - 1] * i;
}

int nCr(int fact[], int n, int r) {
  if (r > n) return 0;

  int res = fact[n] / (fact[r] * fact[n - r]);
  res /= fact[n - r];
  return res;
}

int countWays(vector<int> &arr, int fact[]) {
  int n = arr.size();
  if (n <= 2) return 1;

  vector<int> leftSubTree;
  vector<int> rightSubTree;

  int root = arr[0];

  for (int i = 1; i < n; i++) {
    (arr[i] < root) ? leftSubTree.push_back(arr[i])
                    : rightSubTree.push_back(arr[i]);
  }

  int n1 = leftSubTree.size();
  int n2 = rightSubTree.size();

  int countLeft = countWays(leftSubTree, fact);
  int countRight = countWays(rightSubTree, fact);

  return (nCr(fact, n - 1, n1) * countLeft * countRight);
}

int main() {
  int n, temp;
  vector<int> v;

  cin >> n;
  int size = n;
  while (n > 0) {
    while (n > 0) {
      cin >> temp;
      v.push_back(temp);
      n--;
    }

    size = v.size();
    // int fact[size];

    // calculate
    cin >> n;
  }

  return 0;
}