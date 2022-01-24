/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#ifndef NFA_H
#define NFA_H

#include "State.h"
#include "Parser.h"
#include <vector>
#include <string>
#include <iostream>


class NFA
{
    public:
        // Constructor, Deconstructor
        NFA();
        NFA(Parser parser);
        ~NFA();

        // Getters
        vector<State*> GetStates();
        vector<char> GetAlphabet();
        State* GetStartState();
        vector<State*> GetAcceptStates();

        void ConstructNFA();
        void EpsilonClosure(State* state, vector<State*> &epsilonClosure);

    private:
        // Member variables
        vector<State*> states;
        vector<char> alphabet;
        State* startState;
        vector<State*> acceptStates;
        Parser parser;

        // Helper methods
        void BuildStates();
        void SetAlphabet();
        void SetStartState();
        void SetAcceptStates();
        void SetTransitions();
        State* GetState(char stateName);
        bool IsEPSTransition(string line);
};

#endif