/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#ifndef DFA_H
#define DFA_H

#include "State.h"
#include "NFA.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class DFA
{
    public:
        // Constructor, Deconstructor
        DFA();
        DFA(NFA* nfa);
        ~DFA();

        void ConvertFromNFA();

    private:
        // Helper methods
        void SetStartState();
        void CalculateRemainingStates();


        // Member variables
        vector<State*> states;
        vector<char> alphabet;
        State* startState;
        vector<State*> acceptStates;

        vector<vector<State*>> statesInConstruction;

        NFA* nfa;
};

#endif