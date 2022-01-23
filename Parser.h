/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <algorithm>

#include <iostream>

using namespace std;

class Parser
{
    public:
        // Constructor, Deconstructor
        Parser();
        ~Parser();

        // Getters for member variables
        vector<char> GetParsedStates();
        vector<char> GetParsedAlphabet();
        char GetParsedStartState();
        vector<char> GetParsedAcceptStates();
        vector<string> GetParsedTransitionFunction();

        void parseNFAFile(string nfa);

    private:
        // Helper methods
        void parseStates(string stateLine);
        void parseAlphabet(string alphabetLine);
        void parseStartState(string startStateLine);
        void parseAcceptStates(string acceptStateLine);
        void parseTransitionTable(string NFA);
        string getNextLine(string text);

        // Member variables
        vector<char> states;
        vector<char> alphabet;
        char startState;
        vector<char> acceptStates;
        vector<string> transitionFunction;
        int newlineIndex = 0;
};

#endif