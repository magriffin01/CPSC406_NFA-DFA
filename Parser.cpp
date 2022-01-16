/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "Parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

// Parses the NFA string and fills in the respective member variables
void Parser::parseNFAFile(string nfa)
{
    // Do things using helper methods
    string statesLine = getNextLine(nfa);
    parseStates(statesLine);

    cout << getNextLine(nfa) << "\n";
    cout << getNextLine(nfa) << "\n";
    cout << getNextLine(nfa) << "\n";
}

// Parses the states from the line of text contiaining the states
void Parser::parseStates(string stateLine)
{
    for (int i = 0; i < stateLine.length(); ++i)
    {
        // If char is a bracket or tab character, skip, otherwise push the char onto the states list
        if ((stateLine.at(i) == '{') || (stateLine.at(i) == '}') || (stateLine.at(i) == '\t'))
        {
            continue;
        }

        states.push_back(stateLine.at(i));
    }

    // Testing Only
    for (int i = 0; i < states.size(); ++i)
    {
        cout << "State: " << states[i] << "\n";
    }
}


// Gets the next line of text needed for parsing from the string of text
string Parser::getNextLine(string text)
{
    string line = "";

    // Start i at the current newlineIndex and get the line up to the next newline char
    for (int i = newlineIndex; i < text.length(); ++i)
    {
        if (text.at(i) == '\n')
        {
            cout << "newline" << "\n";
            newlineIndex = i + 1; // Sets the newline index to 1 more than where the newline char was found
            break;
        }

        line += text.at(i);
    }

    return line;
}