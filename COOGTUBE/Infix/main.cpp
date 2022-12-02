#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int priority(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}

string infixToPostfix(string s) {
  stack<char> st;
  string postfix;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ' ') {
    }

    else if (isdigit(s[i]))
      postfix += s[i];

    else if (s[i] == '(')
      st.push('(');

    else if (s[i] == ')') {
      while (st.top() != '(') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }

    else {
      while (!st.empty() && priority(s[i]) <= priority(st.top())) {
        postfix += st.top();
        st.pop();
      }
      st.push(s[i]);
    }
  }

  while (!st.empty()) {
    postfix += st.top();
    st.pop();
  }

  return postfix;
}

int evaluatePostfix(string s) {
  stack<int> st;

  for (int i = 0; i < s.length(); i++) {
    if (isdigit(s[i]))
      st.push(s[i] - '0');
    else {
      int val1 = st.top();
      st.pop();
      int val2 = st.top();
      st.pop();
      switch (s[i]) {
        case '+':
          st.push(val2 + val1);
          break;
        case '-':
          st.push(val2 - val1);
          break;
        case '*':
          st.push(val2 * val1);
          break;
        case '/':
          st.push(val2 / val1);
          break;
      }
    }
  }
  return st.top();
}

string postfixToInfix(string s) {
  stack<string> st;
  for (int i = 0; i < s.length(); i++) {
    if (isdigit(s[i])) {
      string temp(1, s[i]);
      st.push(temp);
    } else {
      string val1 = st.top();
      st.pop();
      string val2 = st.top();
      st.pop();
      st.push("(" + val2 + s[i] + val1 + ")");
    }
  }
  return st.top();
}

int main() {
  string s;
  cin >> s;
  cout << endl;
  cout << "Infix: " << postfixToInfix(s) << endl;
  cout << "Postfix: " << infixToPostfix(s) << endl;
  return 0;
}