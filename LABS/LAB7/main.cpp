#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#include "ArgumentManager.h"

using namespace std;

// BEGIN TA PROVIDED CODE

bool BFS(int **graph, int start, int end, int n) {
  queue<int> q;
  bool *visited = new bool[n];
  for (int i = 0; i < n; i++) visited[i] = false;

  q.push(start);
  int v(0);

  while (!q.empty()) {
    v = q.front();
    q.pop();

    if (v == end) {
      delete[] visited;
      return true;
    } else if (!visited[v])
      visited[v] = true;

    for (int i = 0; i < n; i++)
      if (graph[v][i] != 0 && !visited[i]) q.push(i);
  }

  delete[] visited;
  return false;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  // ifstream input("input3.txt");
  // ofstream output("output1.txt");

  int n, start, end(0);
  input >> n;

  int **graph = new int *[n];
  for (int i = 0; i < n; i++) graph[i] = new int[n];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) graph[i][j] = 0;

  input >> start >> end;

  string inStr;
  int i, j(0);

  while (getline(input, inStr)) {
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
    if (inStr == " " || inStr.empty()) continue;

    i = stoi(inStr.substr(0, inStr.find(' ')));
    j = stoi(inStr.substr(inStr.find(' ') + 1,
                          inStr.length() - inStr.find(' ') - 1));
    graph[i][j] = 1;
    graph[j][i] = 1;
  }

  BFS(graph, start, end, n) ? output << "true" : output << "false";
  return 0;
}

// END TA PROVIDED CODE