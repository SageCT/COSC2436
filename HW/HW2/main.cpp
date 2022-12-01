#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "linkedlist.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ifstream cmd(am.get("command"));
    ofstream out(am.get("output"));

    // ifstream input("input9.txt");
    // ifstream cmd("command9.txt");
    // ofstream out("output1.txt");

    linkedlist<string> creds;

    string in;

    while (getline(input, in))
    {
        in.erase(remove(in.begin(), in.end(), '\n'), in.end());
        in.erase(remove(in.begin(), in.end(), '\r'), in.end());
        in.erase(remove(in.begin(), in.end(), ' '), in.end());

        // Verifying that the input is valid
        if (in.find("id:") != string::npos)
        {
            if (in.find("username:", in.find("id:") + 3) != string::npos)
            {
                if (in.find("score:", in.find("username:") + 8) != string::npos)
                {
                    if (in.find("grade:", in.find("score:") + 5) != string::npos)
                    {
                        cout << in << " Passes." << endl;

                        bool usernamesMatch = false, idsMatch = false;
                        if (creds.getSize() == 0)
                        {
                            cout << in << " Added (size 0)" << endl;
                            creds.addAtTail(in);
                        }

                        else if (creds.getSize() > 0)
                        {
                            for (int x = 0; x < creds.getSize(); x++)
                            {

                                int startIndex1 = in.find("username:") + 9, startIndex2 = creds.returnAtPos(x)->data.find("username:") + 9;
                                int endIndex1 = in.find(";", startIndex1), endIndex2 = creds.returnAtPos(x)->data.find(";", startIndex2);
                                string string1 = in.substr(startIndex1, endIndex1 - startIndex1), string2 = creds.returnAtPos(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (string1.compare(string2) == 0)
                                    usernamesMatch = true;

                                startIndex1 = in.find("ids:") + 4, startIndex2 = creds.returnAtPos(x)->data.find("ids:") + 4;
                                endIndex1 = in.find(";", startIndex1), endIndex2 = creds.returnAtPos(x)->data.find(";", startIndex2);
                                string1 = in.substr(startIndex1, endIndex1 - startIndex1), string2 = creds.returnAtPos(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (string1.compare(string2) == 0 && !usernamesMatch)
                                {
                                    idsMatch = true;
                                    cout << in << " Added (ID Match)" << endl;
                                    creds.removeAtPos(x);
                                    creds.addAtPos(in, x);
                                }
                            }

                            if (!usernamesMatch && !idsMatch && creds.search(in) < 0)
                            {
                                creds.addAtTail(in);
                                cout << in << " Added (No User/ID Match)" << endl;
                            }
                        }
                    }
                }
            }
        }

        // In case the input is empty add regardless
        else if (in == "")
        {
            creds.addAtTail(in);
        }
    }

    if (cmd.peek() != EOF)
    {
        string sortType;
        string in;
        while (getline(cmd, in))
        {
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());

            // If the line is an Add command
            if (in.find("Add") != string::npos)
            {
                // identifying index and creating a string for the new node
                int index = stoi(in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1));
                string toAdd = in.substr(in.find("["), (in.find("]") - in.find("[") + 1));
                if (toAdd.find("id:") != string::npos && toAdd.find("username:") != string::npos && toAdd.find("score:") != string::npos && toAdd.find("grade:") != string::npos)
                {
                    if (index <= creds.getSize())
                    {
                        cout << "index:" << index << " toAdd: " << toAdd << endl;

                        for (int x = 0; x < creds.getSize(); x++)
                        {
                            if (toAdd.substr(toAdd.find(":") + 1, 4).compare(creds.returnAtPos(x)->data.substr(creds.returnAtPos(x)->data.find(":") + 1, 4)) == 0)
                            {
                                cout << "Added " << toAdd << endl;
                                creds.removeAtPos(x);
                                creds.addAtPos(toAdd, x);
                            }
                        }

                        cout << "Passed the id check" << endl;
                        bool usernamesMatch = false, idsMatch = false;
                        if (creds.getSize() == 0 && index <= creds.getSize())
                        {
                            cout << "Added (NO VALUES)" << toAdd << endl;
                            creds.addAtHead(toAdd);
                        }

                        else if (creds.getSize() > 0 && index <= creds.getSize())
                        {

                            for (int x = 0; x < creds.getSize(); x++)
                            {
                                idsMatch = false;
                                int startIndex1 = toAdd.find("username:") + 9, startIndex2 = creds.returnAtPos(x)->data.find("username:") + 9;
                                int endIndex1 = toAdd.find(";", startIndex1), endIndex2 = creds.returnAtPos(x)->data.find(";", startIndex2);
                                string string1 = toAdd.substr(startIndex1, endIndex1 - startIndex1), string2 = creds.returnAtPos(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (string1.compare(string2) == 0)
                                    usernamesMatch = true;

                                startIndex1 = toAdd.find("ids:") + 4, startIndex2 = creds.returnAtPos(x)->data.find("ids:") + 4;
                                endIndex1 = toAdd.find(";", startIndex1), endIndex2 = creds.returnAtPos(x)->data.find(";", startIndex2);
                                string1 = toAdd.substr(startIndex1, endIndex1 - startIndex1), string2 = creds.returnAtPos(x)->data.substr(startIndex2, endIndex2 - startIndex2);
                                if (string1.compare(string2) == 0)
                                    idsMatch = true;

                                if (idsMatch && !usernamesMatch)
                                {
                                    cout << toAdd << "Added (ID MATCH)" << endl;
                                    creds.removeAtPos(x);
                                    creds.addAtPos(toAdd, x);
                                }
                            }

                            if (!usernamesMatch && !idsMatch && creds.search(toAdd) < 0)
                            {
                                cout << toAdd << "Added (NO USER/ ID MATCH)" << endl;
                                creds.addAtPos(toAdd, index);
                            }
                        }
                    }
                }
            }

            // If the line is a Remove command
            else if (in.find("Remove") != string::npos)
            {
                // Identifying the index and creating a string for the new node
                string toFind = in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1);
                cout << "\n"
                     << toFind << " String to Delete" << endl;
                // Removing the node using the found index;
                while (creds.search(toFind) > -1)
                {
                    cout << "Removing " << creds.returnAtPos(creds.search(toFind))->data << endl;
                    creds.removeAtPos(creds.search(toFind));
                }
            }

            // // If the line is a sort command
            else if (in.find("Sort") != string::npos)
            {
                creds.sort(in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1));
                sortType = in.substr(in.find("(") + 1, in.find(")") - in.find("(") - 1);
            }
        }

        // DEBUGGING MAKE SURE TO CHANGE FOR ARGMAN
        creds.print(out);
    }
    return 0;
}