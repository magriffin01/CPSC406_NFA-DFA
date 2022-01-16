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

#include <iostream>

using namespace std;

class Parser
{
    public:
        Parser();
        ~Parser();
        void parseNFAFile(string nfa);

    private:
        void parseStates(string stateLine);
        void parseAlphabet(string alphabetLine);
        void parseStartState(string startStateLine);
        void parseAcceptStates(string acceptStateLine);

        // TODO: Transition Function

        string getNextLine(string text);

        vector<char> states;
        vector<char> alphabet;
        char startState;
        vector<char> acceptStates;

        int newlineIndex = 0;
};

#endif