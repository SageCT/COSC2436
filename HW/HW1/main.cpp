#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char *argv[])
{
    // *** You need to open files using argumentmanager when submit your assignment ***
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ifstream command(am.get("command"));
    // ofstream out(am.get("output"));

    // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
    ifstream input("input1.txt");
    ifstream command("command1.txt");
    ofstream out("output1.txt");

    string in = "";
    int count = 0;
    vector<string> lines;
    vector<string> ids;
    vector<string> lineChars;
    vector<string> decodedLines;
    vector<string> cmds;
    vector<string> postCmd;

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

            // Ensuring the entry is valid, if valid add to lines vector
            int count = 0;
            if (in.find(";id:") != string::npos) // If ;id: is present
            {
                if (isalpha(in[0]))
                {
                    for (auto entry : in)
                    {
                        if (!isalpha(entry) && !isdigit(entry) && entry != ';' && entry != ':' && entry != '#')
                            count++;
                    }

                    if (count == 0)
                        lines.push_back(in);
                }
            }
        }

        // Cutting up the lines and putting ids into their own vectors
        for (auto line : lines)
        {
            string id = line.substr(line.find(";id:") + 4, line.length() - 1);
            ids.push_back(id);

            string lineChar = line.substr(0, line.find("id:"));
            lineChars.push_back(lineChar);
        }

        // Decoding the ids and characters and putting them into a vector
        for (int x = 0; x < ids.size(); x++)
        {
            string decodedLine = "";
            for (int y = 0; y < ids.at(x).length(); y++)
            {
                char selectedChar = ids.at(x).at(y);
                if (isdigit(selectedChar))
                {
                    decodedLine += selectedChar;
                }

                else if (isalpha(selectedChar))
                {
                    if (lineChars.at(x).find(selectedChar) != string::npos)
                    {
                        int startIndex = lineChars.at(x).find(selectedChar) + 2;
                        int endIndex = lineChars.at(x).find(';', startIndex);

                        decodedLine += lineChars.at(x).substr(startIndex, endIndex - startIndex);
                    }
                }
                else if (selectedChar == '#')
                    decodedLine += "#";
            }

            // Replacing the # with the index of the character
            vector<int> hashIndex;
            int lastIndex = 0;

            while (decodedLine.find('#', lastIndex) != string::npos)
            {
                lastIndex = decodedLine.find('#', lastIndex);
                hashIndex.push_back(lastIndex++);
            }
            while (!hashIndex.empty())
            {
                decodedLine.insert(hashIndex.back(), to_string(hashIndex.back()));
                hashIndex.pop_back();
            }
            while (decodedLine.find('#') != string::npos)
                decodedLine.erase(decodedLine.find('#'), 1);

            decodedLines.push_back(decodedLine);
        }

        // Handling command cases
        string cmd = "";
        count = 0;

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
        }

        // Finding the valid indexes within decodedLines and putting them into validIndex
        // Taking the lines from each cmd and puttings the first4 and last4 into their own indexes
        vector<string> first4s, last4s;
        vector<int> validIndex;
        bool first4 = false, last4 = false;

        for (auto line : cmds)
        {
            if (line.find("first4:") != string::npos)
            {
                first4 = true;
                first4s.push_back(line.substr(line.find(':') + 1));
            }

            else if (line.find("last4:") != string::npos)
            {
                last4 = true;
                last4s.push_back(line.substr(line.find(':') + 1));
            }
        }

        // Depending on if the command has only first4, last4, or both
        // Look for the first4 and last4 in decodedLines and put their indexes into validIndex
        if (first4 && last4)
        {
            for (int x = 0; x < decodedLines.size(); x++)
                for (int y = 0; y < first4s.size(); y++)
                    if (first4s.at(y) == decodedLines.at(x).substr(0, 4))
                        for (int z = 0; z < last4s.size(); z++)
                            if (last4s.at(z) == decodedLines.at(x).substr(decodedLines.at(x).size() - 4))
                                validIndex.push_back(x);
        }

        else if (first4 && !last4)
        {
            for (int x = 0; x < cmds.size(); x++)
                for (int y = 0; y < decodedLines.size(); y++)
                    if ((decodedLines.at(y).substr(0, 4)) == (cmds.at(x).substr(cmds.at(x).find(':') + 1)))
                        validIndex.push_back(y);
        }

        else if (!first4 && last4)
        {
            for (int x = 0; x < cmds.size(); x++)
                for (int y = 0; y < decodedLines.size(); y++)
                    if ((decodedLines.at(y).substr(decodedLines.at(y).size() - 4)) == (cmds.at(x).substr(cmds.at(x).find(':') + 1)))
                        validIndex.push_back(y);
        }

        else if (!first4 && !last4)
        {
            for (int x = 0; x < decodedLines.size(); x++)
                postCmd.push_back(decodedLines.at(x));
        }

        // Putting the indexes of validIndex from decodedLines into postCmd vector
        sort(validIndex.begin(), validIndex.end());
        for (int x = 0; x < validIndex.size(); x++)
            postCmd.push_back(decodedLines.at(validIndex.at(x)));

        // Outputting to argumentmanager/output file
        for (int x = 0; x < postCmd.size(); x++)
            (x == postCmd.size() - 1) ? (out << postCmd.at(x)) : (out << postCmd.at(x) << endl);
    }
}