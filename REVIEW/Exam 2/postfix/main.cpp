#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>


using namespace std;

void levelOrder1(int *heap, int size) {
  queue<int> q;
  // printing the root
  q.push(heap[0]);
  string st = to_string(heap[0]);
  cout << st << endl;
  q.pop();
  // Printing children
  int i = 1;
  for (int i = 1; i < size; i++) {
    q.push(heap[i * 2 + 1]);
    q.push(heap[i * 2 + 2]);

    q.pop();
    q.pop();
  }
}

void levelOrder(int heap[], int size) {
  queue<int> q;
  for (int i = 0; i < size; i++) {
    q.push(heap[i]);
  }

  int level = 1;
  int counter = 0;
  for (int i = 0; i < size; i++) {
    if (counter == level) {
      cout << endl;
      level *= 2;
      counter = 0;
    }
    cout << q.front() << " ";
    q.pop();
    counter++;
  }
}

void levelOrder3(int heap[], int size) {
  queue<int> q;
  for (int i = 0; i < size; i++) {
    q.push(heap[i]);
  }
  int j = 0;

  while (size > 0) {
    for (int i = 0; i <= j; i++) {
      int x = q.front();
      cout << x << " ";
      q.pop();
      size--;
    }
    j++;
    cout << endl;
  }
}

int partition(int *arr, int low, int high) {}

// PRIORITIES: * and / then + and - then digits.
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

bool validParentheses(string s) {
  stack<char> st;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
      st.push(s[i]);
      continue;
    }
    char temp;
    switch (s[i]) {
      case ')':
        temp = st.top();
        st.pop();
        if (temp != '(') return false;
        break;
      case '}':
        temp = st.top();
        st.pop();
        if (temp == '(' || temp == '[') return false;
        break;
      case ']':
        temp = st.top();
        st.pop();
        if (temp == '(' || temp == '{') return false;
        break;
    }
  }
  return (st.empty());
}

int main() {
  int heap[15] = {1, 3, 5, 4, 7, 6, 7, 5, 5, 10, 10, 10, 10, 5, 5};
  int size = 15;
  levelOrder3(heap, size);
}
