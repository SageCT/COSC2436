#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "ArgumentManager.h"
using namespace std;

// This function grabs a string value submitted, creates another string swapVal, and then
// goes backwards on the value submitted adding it to the swapVal string created. -- Brendan
string reverseVal(string _num){
  string swapVal = "";
  for(int x = _num.length() - 1; x >= 0; x--){ 
    swapVal += _num[x]; 
    }
  return swapVal;
}


// This recursive function goes through the string value given and finds the parenthesis. Once
// found, it takes the number inside, passes it through the reverseVal function, and replaces
// the parenthesis it took from value. It sends the same value back in and repeats it until all
// parenthsis are removed. -- Brendan
string parRemover(string parValue){
  string _parValue = parValue;
  int parLeft = 0, parRight = 0;
  if(_parValue.find('(') == -1 && _parValue.find(')') == -1){ // returns if no parenthisis is found
    return _parValue;
  }
  for(int x = 0; x < _parValue.length(); x++){ // counts all () in the value
    if(_parValue[x] == '('){
      parLeft++;
    }else if(_parValue[x] == ')'){
      parRight++;
    }
    if(parLeft == parRight && parLeft != 0){ // breaks if outside of bracket scope
      break;
    }
  }
  if(parLeft != parRight){ return "Improper Value"; }
  string subCode = "";
  int posLeft = 0;
  int x = 0;
  while(x < _parValue.length() - 1){
    if(_parValue[x] == '('){
      posLeft++;
    }
    if(_parValue[x] == '(' && posLeft == parLeft){ // finds the last ( in the value
      int i = x + 1;
      while(_parValue[i] != ')'){ // grabs the value inside the parenthsis
        subCode += _parValue[i];
        i++;
      }
      subCode = reverseVal(subCode);
      _parValue.replace(_parValue.begin() + x, _parValue.begin() + i + 1, subCode); // parenthesis is replaced
      _parValue = parRemover(_parValue);
    }
    // else if(_parValue[x + 1] == '(' && posLeft != parLeft){
    //   // posLeft++;
    //   x++;
    // }
    else{
      x++;
    }
  }
  return _parValue;
}


// Sorts a stack from the greatest value to the smallest -- Brendan
stack<string> sortStack(stack<string> &input){
  stack<string> tmpStack;
  while (!input.empty()){
    string tmp = input.top();
    input.pop();
    while(!tmpStack.empty() && stoll(tmpStack.top()) < stoll(tmp)){ // stoll is similar to stoi - google for more info
        input.push(tmpStack.top());
        tmpStack.pop();
    }
    tmpStack.push(tmp);
  }
  return tmpStack;
}


// This function removes a value in bar2 that was found to be equal 
// to a value in bar1 -- Brendan
stack<string> removeStackValue(stack<string> &_bar, int num){
  stack<string> temp;
  int pos = 0;
  for(stack<string> dump1 = _bar; !dump1.empty(); dump1.pop()){
    if(pos == num){
      pos++;
    }
    else{
      temp.push(dump1.top());
      pos++;
    }
  }
  return temp;
}


// This function compares stacks and adds unique values to innocent and
// any similar values to the guilty stack -- Brendan
void inOrOut(stack<string> &bar1, stack<string> &bar2, stack<string> &innocent, stack<string> &guilty){
  stack<string> dump1;
  stack<string> dump2;
  for(dump1 = bar1; !dump1.empty(); dump1.pop()){
    int pos = 0;
    for(dump2 = bar2; !dump2.empty(); dump2.pop()){ 
      if(dump1.top() == dump2.top()){ // Checks for duplicate values
        guilty.push(dump1.top());
        bar2 = removeStackValue(bar2, pos); // Removes the duplicate value from bar2
        break;
      }
      pos++;
    }
    if(dump2.empty() == true){
      innocent.push(dump1.top());
    }
  }
  for(dump2 = bar2; !dump2.empty(); dump2.pop()){
    innocent.push(dump2.top()); // All duplicate values from bar2 have been removed. All others are innocent.
  }
}


int main (int argc, char* argv[])
{
    ArgumentManager am(argc, argv); 
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));
    stack <string> bar1; // holds input from bar1
    stack <string> bar2; // holds input from bar2
    stack <string> innocent; // unique value
    stack <string> guilty; // dupplicate value
    string in = "", value;
    bool bar;
    while (getline(input, in))
    {
        in.erase(remove(in.begin(), in.end(), '\n'), in.end());
        in.erase(remove(in.begin(), in.end(), '\r'), in.end());
        if(in != ""){
            if(in.find("Bar1") != -1){ bar = true; }
            else if(in.find("Bar2") != -1){ bar = false;  }
            else{
            in = parRemover(in);
            if(bar == true){ bar1.push(in); }
            else{ bar2.push(in); }
            }
        }
    } //end of TA-provided code
    inOrOut(bar1, bar2, innocent, guilty);
    innocent = sortStack(innocent);
    guilty = sortStack(guilty);
    // start output :)
    if(!guilty.empty()){
        out << "Guilty:";
        for(stack<string> dump = guilty; !dump.empty(); dump.pop()){
            out << '\n' << dump.top();
        }
    }
    if(!innocent.empty()){
        if(!guilty.empty()){
            out << '\n';
        }
        out << "Innocent:";
        for(stack<string> dump = innocent; !dump.empty(); dump.pop()){
            out << '\n' << dump.top();
        }
    }
}