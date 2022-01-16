/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#ifndef STATE_H
#define STATE_H

#include <string>

using namespace std;

class State
{
    public:
        State();
        ~State();

        void SetStateName(string stateName);
        void SetIsStartState(bool isStartState);
        void SetIsAcceptState(bool isAcceptState);
        string GetStateName();
        bool GetIsStartState();
        bool GetIsAcceptState();

    private:
        string stateName;
        bool isStartState;
        bool isAcceptState;
};

#endif