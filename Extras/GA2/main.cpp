#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "ArgumentManager.h"
#include "PQueueGA.h"

using namespace std;

int priority(char x) {
  if (x == '*' || x == '/')
    return 2;
  else if (x == '+' || x == '-')
    return 1;
  return 0;
}

bool extraPar(string str) {
  stack<char> Stack;
  for (char ch : str) {
    if (ch == ')') {
      char top = Stack.top();
      Stack.pop();
      int elementsInside = 0;
      while (top != '(') {
        elementsInside++;
        top = Stack.top();
        Stack.pop();
      }
      if (elementsInside < 1) {
        return true;
      }
    } else {
      Stack.push(ch);
    }
  }
  return false;
}

string inToPost(string in) {
  int po, pc, co, cc, bo, bc;
  po = pc = co = cc = bo = bc = 0;
  for (int i = 0; i < in.length(); i++) {
    switch (in[i]) {
      case '(':
        po++;
        break;
      case ')':
        pc++;
        break;
      case '{':
        co++;
        break;
      case '}':
        cc++;
        break;
      case '[':
        bo++;
        break;
      case ']':
        bc++;
        break;
    }
  }
  if (po != pc || co != cc || bo != bc) {
    return "Invalid";
  }
  for (int i = 0; i < co; i++) {
    in.replace(in.find('{'), 1, "(");
    in.replace(in.find('}'), 1, ")");
  }
  for (int i = 0; i < bo; i++) {
    in.replace(in.find('['), 1, "(");
    in.replace(in.find(']'), 1, ")");
  }
  if (extraPar(in) == true) {
    return "Invalid";
  }

  cout << in << endl;
  stack<char> ops;
  string post = "";
  int parentheses = 0;
  for (int i = 0; i < in.length(); i++) {
    char s = in[i];
    if (isdigit(s) > 0) {
      post = post + s;
    } else if (s == '(') {
      ops.push(s);
      parentheses++;
    } else {
      if (parentheses > 0) {
        if (s == ')') {
          while (ops.top() != '(' && !ops.empty()) {
            post = post + ops.top();
            ops.pop();
          }
          ops.pop();
          parentheses--;
        } else if (ops.top() == '(')
          ops.push(s);
        else if (!ops.empty() && priority(ops.top()) < priority(s)) {
          ops.push(s);
        } else {
          while (!ops.empty() && priority(ops.top()) >= priority(s)) {
            post = post + ops.top();
            ops.pop();
          }
          ops.push(s);
        }
      } else {
        if (ops.empty()) {
          ops.push(s);
        } else if (priority(ops.top()) < priority(s)) {
          ops.push(s);
        } else {
          while (!ops.empty() && priority(ops.top()) >= priority(s)) {
            post = post + ops.top();
            ops.pop();
          }
          ops.push(s);
        }
      }
    }
  }
  while (!ops.empty()) {
    post = post + ops.top();
    ops.pop();
  }
  return post;
}

float eval(string eq) {
  stack<float> s;
  for (int x = 0; x < eq.length(); x++) {
    if (isdigit(eq[x]) > 0) {
      s.push((float)(eq[x] - '0'));
    } else {
      float rightNum = s.top();
      s.pop();

      float leftNum = s.top();
      s.pop();

      if (rightNum > -1000 && leftNum > -1000) {
        switch (eq.at(x)) {
          case '+':
            s.push(leftNum + rightNum);
            break;
          case '-':
            s.push(leftNum - rightNum);
            break;
          case '*':
            s.push(leftNum * rightNum);
            break;
          case '/':
            s.push(leftNum / rightNum);
            break;
        }
      }
    }
  }
  return s.top();
}

int main(int argc, char* argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  // ifstream input("input3.txt");
  // ofstream output("output1.txt");

  PQueueGA pq;
  while (!input.eof()) {
    node* temp = new node();
    string eq;
    getline(input, eq);
    if (eq.empty()) {
      continue;
    }
    cout << eq << endl;
    string post = inToPost(eq);
    cout << post << endl;
    if (post == "Invalid") {
      cout << endl;
      continue;
    }
    float ans = eval(post);
    cout << ans << endl << endl;
    temp->eq = eq;
    temp->ans = ans;
    pq.enq(temp);
  }
  if (pq.empty()) {
    output << "No Valid Expression";
  } else {
    while (!pq.empty()) {
      node* temp = pq.deq();
      output << temp->eq << endl;
      cout << temp->eq << endl;
    }
  }

  return 0;
}