/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "State.h"

State::State()
{
    
}

State::~State()
{

}

// Setter for 'stateName' member variable
void State::SetStateName(char stateName)
{
    this->stateName = stateName;
}

// Setter for 'isStartState' member variable
void State::SetIsStartState(bool isStartState)
{
    this->isStartState = isStartState;
}

// Setter for 'isAcceptState' member variable
void State::SetIsAcceptState(bool isAcceptState)
{
    this->isAcceptState = isAcceptState;
}

// Setter for 'commbinedStateName'
void State::SetCombinedStateName(string stateName)
{
    combinedStateName = stateName;
}

// Getter for 'stateName' member variable
char State::GetStateName()
{
    return stateName;
}

// Getter for 'isStartState' member variable
bool State::GetIsStartState()
{
    return isStartState;
}

// Getter for 'isAcceptState' member variable
bool State::GetIsAcceptState()
{
    return isAcceptState;
}

string State::GetCombinedStateName()
{
    return combinedStateName;
}

// Getter for the hashmap of trasnition states
unordered_map<string, vector<State*>> State::GetAllTransitions()
{
    return transitionStates;
}

// Return the vector of states corresponding to a particular transition symbol
vector<State*> State::GetTransition(string key)
{
    if (transitionStates.find(key) == transitionStates.end())
    {
        return vector<State*>(0); // Return an empty vector if none exist
    }
    else
    {
        return transitionStates.find(key)->second;
    }
}

// Inserts a vector of states into the hashmap based on the symbol to transition on
void State::InsertTransition(string symbol, vector<State*> states)
{
    transitionStates.insert( {symbol, states} );
}

// Removes the vector of states corresponding to a symbol in the hashmap
void State::RemoveTransition(string symbol)
{
    if (transitionStates.empty())
    {
        return;
    }

    transitionStates.erase(symbol);
}

// Displays the transitions with the symbol and then the transition state
void State::DisplayTransitionStates()
{
    for (auto iterator = transitionStates.begin(); iterator != transitionStates.end(); ++iterator)
    {
        cout << "Transition Symbol: " << iterator->first << '\n';

        for (int i = 0; i < iterator->second.size(); ++i)
        {
            cout << "Transition State: " << iterator->second.at(i)->GetCombinedStateName() << '\n';
        }
    }
}
