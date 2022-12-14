#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// #include <queue>

#include "ArgumentManager.h"
#include "Queue.h"
#include "Stack.h"
using namespace std;

void print(vector<vector<char>> matrix) {
  for (size_t i = 0; i < matrix.size(); i++) {
    for (size_t j = 0; j < matrix[i].size(); j++) cout << matrix[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}

bool isSolved(vector<vector<char>> matrix, size_t row, size_t col) {
  for (size_t i = 0; i < row; i++)
    for (size_t j = 0; j < col; j++)
      if (matrix[i][j] == 'B') return false;

  return true;
}

// Priorities: 1. Up, 2. Right, 3. Down, 4. Left
void moveU(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s;
  int counter = 0;
  char temp;

  for (size_t j = 0; j < col; j++) {
    for (size_t i = 0; i < row; i++) {
      if (matrix[i][j] == 'B') {
        if (!s.isEmpty() && s.peek() == 'B') {
          s.pop();
          s.push('X');
        } else
          s.push(matrix[i][j]);
      } else if (matrix[i][j] == 'X') {
        while (s.getSize() < counter) s.push('O');
        s.push('X');
      }
      counter++;
    }

    while (s.getSize() < counter) s.push('O');

    for (signed long long int i = row - 1; i > -1; i--) matrix[i][j] = s.pop();

    counter = 0;
  }
}

void moveR(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s;
  int counter = 0;
  char temp;

  for (size_t j = 0; j < row; j++) {
    for (signed long long int i = col - 1; i > -1; i--) {
      if (matrix[j][i] == 'B') {
        if (!s.isEmpty() && s.peek() == 'B') {
          s.pop();
          s.push('X');
        } else
          s.push(matrix[j][i]);
      } else if (matrix[j][i] == 'X') {
        while (s.getSize() < counter) s.push('O');
        s.push('X');
      }
      counter++;
    }

    while (s.getSize() < counter) s.push('O');

    for (size_t i = 0; i < col; i++) matrix[j][i] = s.pop();

    counter = 0;
  }
}

void moveD(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s;
  int counter = 0;
  char temp;

  for (size_t j = 0; j < col; j++) {
    for (signed long long int i = row - 1; i > -1; i--) {
      if (matrix[i][j] == 'B') {
        if (!s.isEmpty() && s.peek() == 'B') {
          s.pop();
          s.push('X');
        } else
          s.push(matrix[i][j]);
      } else if (matrix[i][j] == 'X') {
        while (s.getSize() < counter) s.push('O');
        s.push('X');
      }
      counter++;
    }

    while (s.getSize() < counter) s.push('O');

    for (signed long long int i = 0; i < row; i++) matrix[i][j] = s.pop();

    counter = 0;
  }
}

void moveL(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s;
  int counter = 0;
  char temp;

  for (size_t j = 0; j < row; j++) {
    for (size_t i = 0; i < col; i++) {
      if (matrix[j][i] == 'B') {
        if (!s.isEmpty() && s.peek() == 'B') {
          s.pop();
          s.push('X');
        } else
          s.push(matrix[j][i]);
      } else if (matrix[j][i] == 'X') {
        while (s.getSize() < counter) s.push('O');
        s.push('X');
      }
      counter++;
    }

    while (s.getSize() < counter) s.push('O');

    for (signed long long int i = col - 1; i > -1; i--) matrix[j][i] = s.pop();

    counter = 0;
  }
}

bool addPath(Queue &q, Pair p, int move, size_t row, size_t col) {
  Pair temp;
  temp.matrix = p.matrix;
  temp.moves = p.moves;

  switch (move) {
    case 1:
      moveU(temp.matrix, row, col);
      if (temp.matrix != p.matrix) {
        temp.moves += "1";
        q.enqueue(temp);
        return true;
      }
      break;

    case 2:
      moveR(temp.matrix, row, col);
      if (temp.matrix != p.matrix) {
        temp.moves += "2";
        q.enqueue(temp);
        return true;
      }
      break;

    case 3:
      moveD(temp.matrix, row, col);
      if (temp.matrix != p.matrix) {
        temp.moves += "3";
        q.enqueue(temp);
        return true;
      }
      break;

    case 4:
      moveL(temp.matrix, row, col);
      if (temp.matrix != p.matrix) {
        temp.moves += "4";
        q.enqueue(temp);
        return true;
      }
      break;
  }
  return false;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  // ifstream input("test1.txt");
  // ofstream output("output1.txt");

  size_t row;
  size_t col;
  input >> row;  // input row
  input >> col;  // input column

  vector<vector<char>> matrix;  // input matrix

  // reading the matrix from the input
  for (int i = 0; i < row; i++) {
    vector<char> temp;
    for (int j = 0; j < col; j++) {
      char c;
      input >> c;
      temp.push_back(c);
    }
    matrix.push_back(temp);
  }

  Pair temp;
  temp.matrix = matrix;
  temp.moves = "";

  Queue q;
  q.enqueue(temp);

  while (!q.isEmpty()) {
    temp = q.dequeue();
    if (isSolved(temp.matrix, row, col))
      break;
    else {
      addPath(q, temp, 1, row, col);
      addPath(q, temp, 2, row, col);
      addPath(q, temp, 3, row, col);
      addPath(q, temp, 4, row, col);
    }
  }

  // print(temp.matrix);
  output << temp.moves;

  return 0;
}
