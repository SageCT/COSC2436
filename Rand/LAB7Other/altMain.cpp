#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>

#include "ArgumentManager.h"

bool BFS(int **graph, int start, int end, int n) {
  queue<int> q;
  bool *visited = new bool[n];

  for (int i = 0; i < n; i++) {
    visited[i] = false;
  }

  q.push(start);
  int v = 0;

  while (!q.empty()) {
    v = q.front();
    q.pop();

    if (v == end) {
      delete[] visited;
      return true;
    }

    else if (!visited[v]) {
      visited[v] = true;
    }

    for (int i = 0; i < n; i++) {
      if (graph[v][i] != 0 && !visited[i]) {
        q.push(i);
      }
    }
  }

  delete[] visited;
  return false;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);

  string input = am.get("input");
  string output = am.get("output");

  ofstream ofs(output);
  ifstream ifs(input);

  int n, start, end = 0;
  ifs >> n;
  int **graph = new int *[n];

  for (int i = 0; i < n; i++) {
    graph[i] = new int[n];
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) graph[i][j] = 0;

  ifs >> start;
  ifs >> end;

  string inStr;

  int i, j = 0;

  while (getline(ifs, inStr)) {
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());

    if (inStr == " " || inStr.length() == 0) continue;

    i = stoi(inStr.substr(0, inStr.find(' ')));
    j = stoi(inStr.substr(inStr.find(' ') + 1,
                          inStr.length() - inStr.find(' ') - 1));
  }

  graph[i][j] = 1;
  graph[j][i] = 1;

  if (BFS(graph, start, end, n)) {
    ofs << "true" << endl;
  }

  else
    ofs << "false" << endl;

  return 0;
}