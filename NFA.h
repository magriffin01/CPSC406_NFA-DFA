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
#include <vector>

class NFA
{
    public:
        NFA();
        ~NFA();

    private:
        vector<State> states;
        vector<string> alphabet;
        State startState;
        vector<State> acceptStates;

        // Needed?
        // vector<vector<State>> *transitions;
};

#endif