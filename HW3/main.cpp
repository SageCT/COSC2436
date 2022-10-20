#include "ArgumentManager.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isSolved(vector<vector<char>> matrix, size_t row, size_t col)
{
  for (size_t i = 0; i < row; i++)
    for (size_t j = 0; j < col; j++)
      if (matrix[i][j] == 'B')
        return false;

  return true;
}

int shiftU(vector<vector<char>> &matrix, size_t row, size_t col)
{
  Stack s;
  int counter = 0;
  char temp;

  for (int j = 0; j < col; j++)
  {
    for (int i = 0; i < row; i++)
    {
      if (matrix[i][j] != 'O' && matrix[i][j] == 'X')
      {
        if (!s.isEmpty() && s.peek() == 'B')
        {
          temp = s.pop();
          s.push('X');
        }
        else
          s.push(matrix[i][j]);
      }
      else if (matrix[i][j] != 'X')
      {
        while (s.getSize() < counter)
          s.push('O');
        s.push('X');
      }
      counter++;
    }

    while (s.getSize() < counter)
      s.push('O');

    for (int i = row - 1; i >= 0; i--)
      matrix[i][j] = s.pop();

    counter = 0;
  }
}

int shiftD(int n)
{
  return 0;
}

int shiftL(int n)
{
  return 0;
}

int shiftR(int n)
{
  return 0;
}

vector<vector<int>> solveMatrix(vector<vector<int>> m)
{
  return m;
}

int main(int argc, char *argv[])
{
  // ArgumentManager am(argc, argv);
  // ifstream input(am.get("input"));
  // ofstream output(am.get("output"));

  ifstream input("input1.txt");
  ofstream output("output1.txt");

  size_t row;
  size_t col;
  input >> row; // input row
  input >> col; // input column

  vector<vector<char>> matrix; // input matrix

  // reading the matrix from the input
  for (int i = 0; i < row; i++)
  {
    vector<char> temp;
    for (int j = 0; j < col; j++)
    {
      char c;
      input >> c;
      temp.push_back(c);
    }
    matrix.push_back(temp);
  }

  // Printing out the initial matrix
  for (int x = 0; x < matrix.size(); x++)
  {
    for (int c = 0; c < matrix.at(x).size(); c++)
    {
      cout << matrix[x][c] << " ";
    }
    cout << endl;
  }

  return 0;
}
