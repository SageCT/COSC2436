#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
void parseMenu(set<string>& menu, set<string>& nameSet, string order);
void displayMenuName(vector<string> menu, vector<string> name,
                     vector<string> orderInfo);
// void displayData(vector<string>& menu); for debugging purpose

int main() {
  int customer;

  cin >> customer;
  cin.ignore();
  while (customer != 0) {
    vector<string> orderInfo;
    set<string> menuSet;
    set<string> nameSet;
    vector<string> menuVec;
    vector<string> nameVec;

    for (int index = 0; index < customer; index++) {
      string order;
      getline(cin, order);
      parseMenu(menuSet, nameSet, order);
      orderInfo.push_back(order);
    }
    copy(menuSet.begin(), menuSet.end(),
         back_inserter(menuVec));  // convert set into vector for sorting
    copy(nameSet.begin(), nameSet.end(), back_inserter(nameVec));
    sort(menuVec.begin(), menuVec.end());
    sort(nameVec.begin(), nameVec.end());
    sort(orderInfo.begin(), orderInfo.end());
    displayMenuName(menuVec, nameVec, orderInfo);
    cin >> customer;
    cin.ignore();
    cout << endl;
  }
}

void displayMenuName(vector<string> menu, vector<string> name,
                     vector<string> orderInfo) {
  for (vector<string>::iterator it = menu.begin(); it != menu.end(); it++) {
    string menuName = *it;
    cout << menuName << " ";
    for (int i = 0; i < name.size(); i++) {
      if (orderInfo[i].find(menuName) != string::npos) {
        cout << name[i] << " ";
      }
    }
    cout << endl;
  }
}

void parseMenu(set<string>& menu, set<string>& nameSet, string order) {
  stringstream ss(order);  // split the order input based on space
  string name;
  string menuName;
  ss >> name;
  nameSet.insert(name);

  while (ss >> menuName) {
    if (menu.find(menuName) == menu.end()) {
      menu.insert(menuName);
    }
  }
}

/*
void displayData(vector<string>& menu)
{
        cout << "*****" << endl;
        for(vector<string>::iterator it=menu.begin(); it != menu.end(); ++it)
                cout << *it << endl;
}
*/