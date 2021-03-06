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

// Returns the vector of char containing the state names
vector<char> Parser::GetParsedStates()
{
    return states;
}

// Returns the vector of char contnaining the alphabet
vector<char> Parser::GetParsedAlphabet()
{
    return alphabet;
}

// Returns the state name of the start state
char Parser::GetParsedStartState()
{
    return startState;
}

// Returns the vector of char contianing the valid accept states
vector<char> Parser::GetParsedAcceptStates()
{
    return acceptStates;
}

// Returns the vector of strings containg the transitions
vector<string> Parser::GetParsedTransitionFunction()
{
    return transitionFunction;
}

// Parses the NFA string and fills in the respective member variables
void Parser::parseNFAFile(string nfa)
{
    // Do things using helper methods
    parseStates(getNextLine(nfa));
    parseAlphabet(getNextLine(nfa));
    parseStartState(getNextLine(nfa));
    parseAcceptStates(getNextLine(nfa));
    parseTransitionTable(nfa);
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
}

// Parses the alphabet from the line of text containing the alphabet
void Parser::parseAlphabet(string alphabetLine)
{
    for (int i = 0; i < alphabetLine.length(); ++i)
    {
        if ((alphabetLine.at(i) == '\t'))
        {
            continue;
        }

        alphabet.push_back(alphabetLine.at(i));
    }
}

// Parse the start state from the line of text containing the start state
void Parser::parseStartState(string startStateLine)
{
    for (int i = 0; i < startStateLine.length(); ++i)
    {
        if ((startStateLine.at(i) == '{') || (startStateLine.at(i) == '}'))
        {
            continue;
        }
        else if (find(states.begin(), states.end(), startStateLine.at(i)) == states.end()) // Check to see if the start state is actually a valid state
        {
            cout << "Specified start state does not exist, please check the file and try again" << '\n';
            return;
        }

        startState = startStateLine.at(i);
    }
}

// Parse the accept states from the line of text containg the accept states
void Parser::parseAcceptStates(string acceptStateLine)
{
    for (int i = 0; i < acceptStateLine.length(); ++i)
    {
        if ((acceptStateLine.at(i) == '{') || (acceptStateLine.at(i) == '}') || (acceptStateLine.at(i) == '\t'))
        {
            continue;
        }
        else if (find(states.begin(), states.end(), acceptStateLine.at(i)) == states.end()) // Check to see if the accept state is a valid state
        {
            cout << '{' << acceptStateLine.at(i) << '}' << " is not a valid state. Please check the file and try again" << '\n';
            continue;
        }

        acceptStates.push_back(acceptStateLine.at(i));
    }
}

// Parse the transition table line from the given text
void Parser::parseTransitionTable(string NFA)
{
    // Initialize two empty strings, one will contain the entire line, the other containing solely the transition states and symbol
    string line = "";
    string transition = "";

    if (newlineIndex == -1) // In the case there are no transitions in the file (EOF already reached)
    {
        cout << "Reached the end of file without finding any transitions. Please check the file and try again." << '\n';
        return;
    }

    // Loop through the remaining lines in the file
    while (newlineIndex != -1)
    {
        line = getNextLine(NFA);

        // Checks each character in the line and performs the corresponding action based on the character
        for (int i = 0; i < line.length(); ++i)
        {
            if ((line.at(i) == '{') || (line.at(i) == '}') || (line.at(i) == ' ') || (line.at(i) == ',') || (line.at(i) == '=') || (line.at(i) == 'P') || (line.at(i) == 'S'))
            {
                continue;
            }
            else if ((line.at(i) == 'E') && (line.at(i + 1) == 'P') && (line.at(i + 2) == 'S'))
            {
                i = i + 2;
                transition += "EPS,";
            }
            else if ((line.at(i) == 'E') && ((line.at(i + 1) != 'P') || (line.at(i + 2) != 'S'))) // Character is 'E' but next characters are not for 'EPS'
            {
                continue;
            }
            else
            {
                transition = transition + line.at(i) + ",";
            }
        }

        transitionFunction.push_back(transition);
        transition = "";
    }
}

// Gets the next line of text needed for parsing from the string of text
string Parser::getNextLine(string text)
{
    string line = "";

    // Start i at the current newlineIndex and get the line up to the next newline char
    for (int i = newlineIndex; i <= text.length(); ++i)
    {
        if (i == text.length()) // If EOF reached, set newlineIndex to -1
        {
            newlineIndex = -1;
            break;
        }
        if (text.at(i) == '\n')
        {
            newlineIndex = i + 1; // Sets the newline index to 1 more than where the newline char was found
            break;
        }

        line += text.at(i);
    }

    return line;
}