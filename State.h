/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class State
{
    public:
        // Constructor, Deconstructor
        State();
        ~State();

        // Setters, Getters
        void SetStateName(char stateName);
        void SetIsStartState(bool isStartState);
        void SetIsAcceptState(bool isAcceptState);
        void SetCombinedStateName(string stateName);
        char GetStateName();
        bool GetIsStartState();
        bool GetIsAcceptState();
        string GetCombinedStateName();
        unordered_map<string, vector<State*>> GetAllTransitions();
        vector<State*> GetTransition(string key);

        void InsertTransition(string symbol, vector<State*> states);
        void RemoveTransition(string symbol);

        // TODO: Delete once complete, testing only
        void DisplayTransitionStates();

    private:
        // Member variables
        char stateName;
        string combinedStateName;
        bool isStartState = false;
        bool isAcceptState = false;
        unordered_map<string, vector<State*>> transitionStates;
};

#endif