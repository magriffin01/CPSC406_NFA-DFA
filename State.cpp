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
void State::SetStateName(string stateName)
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

// Getter for 'stateName' member variable
string State::GetStateName()
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

