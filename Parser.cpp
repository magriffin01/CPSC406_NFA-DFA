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
    parseStates(getNextLine(nfa));
    parseAlphabet(getNextLine(nfa));
    parseStartState(getNextLine(nfa));
    parseAcceptStates(getNextLine(nfa));
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

    // TODO: Delete once finished
    // Testing Only
    for (int i = 0; i < states.size(); ++i)
    {
        cout << "State: " << states[i] << "\n";
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

    // TODO: Delete once finished
    // Testing only
    for (int i = 0; i < alphabet.size(); ++i)
    {
        cout << "Symbol: " << alphabet[i] << "\n";
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

    // TODO: Delete once finished
    cout << "Start State: " << startState << "\n";
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

    // TODO: Delete once done
    // Testing only
    for (int i = 0; i < acceptStates.size(); ++i)
    {
        cout << "Accept State: " << acceptStates[i] << '\n';
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
            newlineIndex = i + 1; // Sets the newline index to 1 more than where the newline char was found
            break;
        }

        line += text.at(i);
    }

    return line;
}