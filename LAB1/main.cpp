#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

// The recursive function
bool found(vector<vector<int>>arr, vector<vector<bool>>&visited, int r, int c, int targetSum, int curSum) {
  // base case
  if (r < 0 || c < 0 || r >= arr.size() || c >= arr[0].size() || visited[r][c] == true) {
    return false;
  }

  // keep track with the curSum
  curSum += arr[r][c];
  
  if (curSum == targetSum) {
    return true;
  }

  // mark visited
  visited[r][c] = true;

  // recursion to move around
  bool foundSequence = found(arr, visited, r - 1, c, targetSum, curSum) ||
              found(arr, visited, r + 1, c, targetSum, curSum) ||
              found(arr, visited, r, c - 1, targetSum, curSum) ||
              found(arr, visited, r, c + 1, targetSum, curSum);

  // unmark visited
  visited[r][c] = false;  

  return foundSequence;
}

int main(int argc, char *argv[]) {
  // Argument manager
  ArgumentManager am(argc, argv);
  ifstream inputFile(am.get("input"));
  ofstream outputFile(am.get("output"));

  // remove when you are ready to submit
  // ifstream inputFile("lab1/input1.txt"); 
  // ofstream outputFile("lab1/output1.txt"); 

  // check if the input file is empty
  if (inputFile.peek() == EOF) {
    outputFile << "Not possible" << endl;
    inputFile.close();
    outputFile.close();
    return 0;
  }

  int row, col;
  int targetSum;
  bool foundSequence = false;
  
  inputFile >> row >> col;

  vector<vector<int>>array(row, vector<int>(col, 0));
  // visited vector to avoid going back to the previous positions
  vector<vector<bool>>visited(row, vector<bool>(col, false));

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      inputFile >> array[i][j];
    }
  }

  inputFile >> targetSum;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (array[i][j] == 0 && found(array, visited, i, j, targetSum, 0)) {
        foundSequence = true;
      }
    }
  }

  // write the result out to output file. 
  if (foundSequence == true) {
    outputFile << "Possible" << endl;
  }
  else {
    outputFile << "Not Possible" << endl;
  }

  inputFile.close();
  outputFile.close();

  return 0;
}