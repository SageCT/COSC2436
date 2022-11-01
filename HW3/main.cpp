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
    for (signed long long int i = row - 1; i > -1; i--) {
      if (matrix[i][j] == 'B') {
        if (!s.isEmpty() && s.peek() == 'B') {
          s.pop();
          s.push('X');
        } else
          s.push(matrix[i][j]);
        while (s.getSize() < counter) s.push('O');
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
  Stack s, r;
  int counter = 0;
  char temp;

  // j = row, i = col
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

    for (int i = col - 1; i >= 0; i--) matrix[j][i] = s.pop();

    counter = 0;
  }
}

void moveD(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s, r;
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

    for (int i = row - 1; i >= 0; i--) matrix[i][j] = s.pop();

    counter = 0;
  }
}

void moveL(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s, r, t;
  int counter = 0;
  char temp;

  // j = col, i = row
  for (size_t j = 0; j < col; j++) {
    for (size_t i = 0; i < row; i++) {
      if (matrix[i][j] == 'B') {
        if (!s.isEmpty() && s.peek() == 'B') {
          s.pop();
          s.push('X');
        } else {
          t.push('B');
          for (int x = i + 2; x < row; x++) {
            if (matrix[x][j] != 'X') {
              t.push('O');
            } else {
              t.push('X');
            }
          }
          while (!t.isEmpty()) s.push(t.pop());
        }
      } else if (matrix[i][j] == 'X') {
        while (s.getSize() < counter) s.push('O');
        s.push('X');
      }
      counter++;
    }

    while (s.getSize() < counter) s.push('O');
    while (!s.isEmpty()) r.push(s.pop());

    for (int i = 0; i <= col - 1; i++) matrix[i][j] = r.pop();

    counter = 0;
  }
}

void moveTest(vector<vector<char>> &matrix, size_t row, size_t col) {
  Stack s, b;
  int counter = 0;
  char temp;

  for (size_t j = 0; j < col; j++) {
    for (signed long long int i = 0; i < row; i++) {
      if (matrix[i][j] == 'B') {
        if (!b.isEmpty() && b.peek() == 'B') {
          b.pop();
          s.push('X');
        } else {
          b.push(matrix[i][j]);
        }
      } else if (matrix[i][j] == 'X') {
        s.push('X');
      }
      counter++;
    }
    while (!b.isEmpty()) s.push(b.pop());
    while (s.getSize() < counter) s.push('O');

    for (signed long long int i = 0; i < row; i++) matrix[i][j] = s.pop();

    counter = 0;
  }
}

void addPath(Queue &q, Pair p, int move, size_t row, size_t col) {
  Pair temp;
  temp.matrix = p.matrix;
  temp.moves = p.moves;

  cout << "Before Move: " << endl;
  print(temp.matrix);

  switch (move) {
    case 1:
      moveU(temp.matrix, row, col);
      cout << "After MoveU: " << endl;
      if (temp.matrix != p.matrix) {
        temp.moves += "1";
        q.enqueue(temp);
      }
      break;

    case 2:
      moveR(temp.matrix, row, col);
      cout << "After MoveR: " << endl;
      if (temp.matrix != p.matrix) {
        temp.moves += "2";
        q.enqueue(temp);
      }
      break;

    case 3:
      moveD(temp.matrix, row, col);
      cout << "After MoveD: " << endl;
      if (temp.matrix != p.matrix) {
        temp.moves += "3";
        q.enqueue(temp);
      }
      break;

    case 4:
      moveL(temp.matrix, row, col);
      cout << "After MoveL: " << endl;
      if (temp.matrix != p.matrix) {
        temp.moves += "4";
        q.enqueue(temp);
      }
      break;
  }
  print(temp.matrix);
}

int main(int argc, char *argv[]) {
  // ArgumentManager am(argc, argv);
  // ifstream input(am.get("input"));
  // ofstream output(am.get("output"));

  ifstream input("test.txt");
  ofstream output("output1.txt");

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

  print(matrix);
  moveTest(matrix, row, col);
  print(matrix);

  // while (!q.isEmpty()) {
  //   temp = q.dequeue();
  //   if (isSolved(temp.matrix, row, col)) {
  //     if (temp.moves == "") {
  //       cout << 0;
  //     } else {
  //       cout << temp.moves;
  //     }
  //   } else {
  //     string change = temp.moves; 123
  //     if (change.back() != '1')
  //       addPath(q, temp, 1, row, col);
  //     else if (change.back() != '2')
  //       addPath(q, temp, 2, row, col);
  //     else if (change.back() != '3')
  //       addPath(q, temp, 3, row, col);
  //     else if (change.back() != '4')
  //       addPath(q, temp, 4, row, col);
  //   }
  // }

  // for (int i = temp.moves.length() - 1; i > -1; i--) {

  //   char c = temp.moves[i];
  //   cout << c << endl;
  //   switch (c) {
  //     case '1':
  //       moveU(temp.matrix, row, col);
  //       break;
  //     case '2':
  //       moveD(temp.matrix, row, col);
  //       break;
  //     case '3':
  //       moveL(temp.matrix, row, col);
  //       break;
  //     case '4':
  //       moveR(temp.matrix, row, col);
  //       break;
  //   }
  //   print(temp.matrix);
  // }

  return 0;
}
