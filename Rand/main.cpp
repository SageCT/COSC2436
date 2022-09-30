/*
You will implement a C++ program to decode different string of number from the
input file then filtering out the information requested by the command file.
This assignment focusses on array management and string handling in C++. You
will also learn about string manipulation with predefined string utility
functions and basic file operations.
*/

/*
- The input file will contain a list of encoded id number. The input can range
anywhere from 0 to 100 entries. Input might contain empty lines and spaces
(empty lines and spaces need to be removed to process each entry correctly).
- Each entry will be on its own line and have 2 different parts, coded
characters set and id string.
- The id string will consist of digits, alphabet characters, and the hash sign.
- Alphabet characters in the id string will always have a number representation
for it in the characters set, separated by a colon.
- Semicolon is used to separate characters in the set and id string.
- The id string will always come after the characters set in the entry.
- Valid entry should have all 2 parts, the characters set and the id string.
- Invalid entry should be ignored.
*/

/*
- The command file will contain different criteria for filtering out id.
- There will be a total of two types (case sensitive): “first4” and “last4”.
- first4: those id that have its first 4 digits match with the value given in
the command.
- last4: those id that have its last 4 digits match with the value given in the
command.
- The criteria and its value will be separated by a colon. Ex: “first4:1234”,
“last4:6789”.
- If multiple value appears for the same criteria in the command file, then as
long as the id satisfy one of those value then it should be printed to the
output.
- Ex: “first4:1234”, “first4:6789” => id that have 1234 or 6789 as the first 4
digits should be printed to the output.
- If both criteria appear in the command file, then the id must satisfy with one
of the values of each criteria in order to be in the output.
- Ex: “first4:1234”, “first4:6789”, “last4:1357”, “last4:2468” = > id that have
1234 or 6789 as the first 4 digits and 1357 or 2468 as the last 4 digits should
be printed to the output.
- Each value in the command will be on its own line, there might be empty lines
and spaces.
- If the command is empty, all the valid id should be printed to the output.
- The output file should contain all the valid id filtered out by the command
file in the order they appeared in the input file (empty lines and spaced should
be removed).
- Each entry should be on its own line.
- If there are no id that satisfy the criteria in the command file, then the
output file should be empty.
*/

#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    // You need to open files using argumentmanager when submit your assignment.
  ArgumentManager am(argc, argv);
//   ifstream input(am.get("input"));
//   ifstream command(am.get("command"));
//   ofstream out(am.get("output"));


    // Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment
    ifstream input("input1.txt");
    ifstream command("command1.txt");
    ofstream out("output1.txt");

    vector<string> cmds; //for command
		vector<string> postCmd; //also for command
		vector<string> lines; //to hold the input
		vector<string> ID; //ID
		vector<string> keyValues; //key Values
		vector<string> replacements; //the replacement string
		vector<string> firstPart, lastPart; //for command
    vector<int> rightIndex; // valid Index checking
	
    string in = "";
    if (input.peek() != EOF)
    {
        while (getline(input, in))
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in.size() == 0)
                continue;
            // continue to process the input below
						
						//amke sure the entry is valid
						int num = 0;
            if (in.find(";id:") != string::npos) // If ;id: is present
            {
                if (isalpha(in[0]))
                {
                    for (auto entry : in)
                    {
                        if (!isalpha(entry) && !isdigit(entry) && entry != ';' && entry != ':' && entry != '#')
												{
                          num++;
												}
										}
                    if (num == 0)
                        lines.push_back(in);
                }
            }
        }
        //Separating the ID and keyValues into their own vectors
        for (auto line : lines)
        {
            string id = line.substr(line.find(";id:") + 4, line.length() - 1);
            ID.push_back(id);
            string keyValue = line.substr(0, line.find("id:"));
            keyValues.push_back(keyValue);
        }
        // replace the letters in the ID array with the key values from the keyValue array
        for (int a = 0; a < ID.size(); a++)
        {
            string replacement = "";
            for (int b = 0; b < ID.at(a).length(); b++)
            {
                char currentLetter = ID.at(a).at(b);
                if (isdigit(currentLetter))
                {
                    replacement += currentLetter;
                }

                else if (isalpha(currentLetter))
                {
                    if (keyValues.at(a).find(currentLetter) != string::npos)
                    {
                        int startValue = keyValues.at(a).find(currentLetter) + 2;
                        int endValue = keyValues.at(a).find(';', startValue);
                        replacement += keyValues.at(a).substr(startValue, endValue - startValue);
                    }
								}
								else if (currentLetter == '#')
								{
                    replacement += "#";
								}
						}
					// replace # with the index
            vector<int> hashtagIndex;
            int lastIndex = 0;

            while (replacement.find('#', lastIndex) != string::npos)
            {
                lastIndex = replacement.find('#', lastIndex);
                hashtagIndex.push_back(lastIndex++);
            }
            while (!hashtagIndex.empty())
            {
                replacement.insert(hashtagIndex.back(), to_string(hashtagIndex.back()));
                hashtagIndex.pop_back();
            }
            while (replacement.find('#') != string::npos)
						{
              replacement.erase(replacement.find('#'), 1);
						}
					replacements.push_back(replacement);
				}

        string cmd = "";
        while (getline(command, cmd))
        {
            // Clean up blank spaces, \n and \r, and skip blank lines
            cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
            cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
            cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
            if (cmd.size() == 0)
                continue;
            // continue to process the command below
						cmds.push_back(cmd);
            bool firstCmd = false, lastCmd = false; // check if it has a first/last 4, set to false by default
            for (auto line : cmds)
            {
                if (line.find("first4: ") != string::npos) // check if it has a first4
                {
                    firstCmd = true;                                      // set to true
                    firstPart.push_back(line.substr(line.find(':') + 1)); // add to vector
                }
                else if (line.find("last4:") != string::npos) // check if it has a last4
                {
                    lastCmd = true;                                      // set to true
                    lastPart.push_back(line.substr(line.find(':') + 1)); // add to vector
                }
            }
            // Look at first 4 and last 4 values in replacement and place their indexes into rightIndex if the command has first4/last4/both
            if (firstCmd && lastCmd)
            {
                for (int a = 0; a < replacements.size(); a++)
                {
                    for (int b = 0; b < firstPart.size(); b++)
                    {
                        if (firstPart.at(b) == replacements.at(a).substr(0, 4))
                        {
                            for (int c = 0; c < lastPart.size(); c++)
                            {
                              if (lastPart.at(c) == replacements.at(a).substr(replacements.at(a).size() - 4))
                              {
                                rightIndex.push_back(a);
                              }
                            }
                        }
                    }
                }
            }
            else if (firstCmd && !lastCmd)
            {
                for (int a = 0; a < cmds.size(); a++)
                {
                    for (int b = 0; b < replacements.size(); b++)
                    {
                        if ((replacements.at(b).substr(0, 4)) == (cmds.at(a).substr(cmds.at(a).find(':') + 1)))
                        {
                            rightIndex.push_back(b);
                        }
                    }
                }
            }
            else if (!firstCmd && lastCmd)
            {
                for (int a = 0; a < cmds.size(); a++)
                {
                    for (int b = 0; b < replacements.size(); b++)
                    {
                        if ((replacements.at(b).substr(replacements.at(b).size() - 4)) == (cmds.at(a).substr(cmds.at(a).find(':') + 1)))
                        {
                            rightIndex.push_back(b);
                        }
                    }
                }
            }
            else if (!firstCmd && !lastCmd)
            {
                for (int x = 0; x < replacements.size(); x++)
                {
                    postCmd.push_back(replacements.at(x));
                }
            }
            // Put the index of rightIndex from replacement into postCmd Vector
            sort(rightIndex.begin(), rightIndex.end());
            for (int x = 0; x < rightIndex.size(); x++)
            {
                postCmd.push_back(replacements.at(rightIndex.at(x)));
            }
            for (auto line : postCmd)
            {
                out << line << "\n";
            }
        }
    }
}