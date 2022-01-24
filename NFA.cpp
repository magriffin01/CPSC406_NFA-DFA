/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "NFA.h"

NFA::NFA()
{

}

NFA::NFA(Parser parser)
{
    this->parser = parser;
}

NFA::~NFA()
{
    for (int i = 0; i < states.size(); ++i)
    {
        delete states[i];
    }
}

// Returns the vector of state pointers
vector<State*> NFA::GetStates()
{
    return states;
}

// Returns the vector of char
vector<char> NFA::GetAlphabet()
{
    return alphabet;
}

// Returns the pointer to the start state
State* NFA::GetStartState()
{
    return startState;
}

// Returns the vector of state pointers that are accept states
vector<State*> NFA::GetAcceptStates()
{
    return acceptStates;
}

// Builds the NFA resulting from the work the parser has done on the file
void NFA::ConstructNFA()
{
    BuildStates();
    SetAlphabet();
    SetStartState();
    SetAcceptStates();
    SetTransitions();
}


// Computes the epislon closure of a given state
void NFA::EpsilonClosure(State* state, vector<State*> &epsilonClosure)
{
    // Push itself
    epsilonClosure.push_back(state);

    vector<State*> epsilonTransition = state->GetTransition("EPS"); // Get the transitions for EPS

    if (epsilonTransition.size() == 0)
    {
        return;
    }

    // Check for duplicates that could result in an infinite loop and delete them
    for (int i = 0; i < epsilonTransition.size(); ++i)
    {
        for (int j = 0; j < epsilonClosure.size(); ++j)
        {
            if (epsilonTransition[i] == epsilonClosure[j])
            {
                epsilonTransition.erase(epsilonTransition.begin() + i);
            }
        }
    }

    for (int i = 0; i < epsilonTransition.size(); ++i)
    {
        EpsilonClosure(epsilonTransition[i], epsilonClosure);
    }
    
}

// Makes a state for each state from the parser
void NFA::BuildStates()
{
    for (int i = 0; i < parser.GetParsedStates().size(); ++i)
    {
        State* stateToAdd = new State();
        stateToAdd->SetStateName(parser.GetParsedStates()[i]);
        states.push_back(stateToAdd);
    }
}

// Sets the alphabet in the NFA
void NFA::SetAlphabet()
{
    alphabet = parser.GetParsedAlphabet();
}

// Sets the start state
void NFA::SetStartState()
{
    for (int i = 0; i < states.size(); ++i)
    {
        if (states[i]->GetStateName() == parser.GetParsedStartState())
        {
            states[i]->SetIsStartState(true);
            startState = states[i];
        }
    }
}

// Sets the accept states
void NFA::SetAcceptStates()
{
    for (int i = 0; i < states.size(); ++i)
    {
        for (int j = 0; j < parser.GetParsedAcceptStates().size(); ++j)
        {
            if (states[i]->GetStateName() == parser.GetParsedAcceptStates()[j])
            {
                states[i]->SetIsAcceptState(true);
                acceptStates.push_back(states[i]);
            }
        }
    }
}

// Fills in the transition hash map in each of the states
void NFA::SetTransitions()
{
    char stateName;
    State* state;
    State* transitionState;
    string originalTransitionSymbol;
    string newTransitionSymbol;
    vector<State*> transitions;

    for (int i = 0; i < parser.GetParsedTransitionFunction().size(); ++i)
    {
        stateName = parser.GetParsedTransitionFunction()[i][0]; // Gets the first character (state to transition from) in the parsed transition function
        state = GetState(stateName); // Get the state corresponding to that character

        // If state is nullptr, it wasn't found
        if (state == nullptr)
        {
            return;
        }

        // Get the transition symbol to transition on and handle case of "EPS"
        originalTransitionSymbol = parser.GetParsedTransitionFunction()[i][2];
        if (IsEPSTransition(parser.GetParsedTransitionFunction()[i]))
        {
            originalTransitionSymbol = "EPS";
        }

        newTransitionSymbol = originalTransitionSymbol; // Change the new variable so set as old to enter loop
        
        // Because a single state can have multiple transitions on the same variable, while loop for vector push back
        while ((state == GetState(stateName)) && ((newTransitionSymbol == originalTransitionSymbol)))
        {
            if (newTransitionSymbol == "EPS") // Spacing is different if the transition symbol is EPS versus a single character
            {
                transitionState = GetState(parser.GetParsedTransitionFunction()[i][6]);
            }
            else
            {
                transitionState = GetState(parser.GetParsedTransitionFunction()[i][4]);
            }
            transitions.push_back(transitionState); // Push state onto transitions vector

            ++i;
            if (i >= parser.GetParsedTransitionFunction().size()) // If i bigger than size of transition function, break out of loop
            {
                break;
            }

            state = GetState(parser.GetParsedTransitionFunction()[i][0]); // Get the next state in the transition function
            newTransitionSymbol = parser.GetParsedTransitionFunction()[i][2];
            if (IsEPSTransition(parser.GetParsedTransitionFunction()[i]))
            {
                newTransitionSymbol = "EPS";
            }
        }

        // Decrement i and get the original state
        --i;
        state = GetState(parser.GetParsedTransitionFunction()[i][0]);

        // Insert the transitions into the hash map in the state and clear the vector
        state->InsertTransition(originalTransitionSymbol, transitions);
        transitions.clear();
    }
}

// Returns the state pointer corresponding to the passed in stateName from the states vector
State* NFA::GetState(char stateName)
{
    for (int i = 0; i < states.size(); ++i)
    {
        if (states[i]->GetStateName() == stateName)
        {
            return states[i];
        }
    }

    return nullptr;
}

// Method that checks whether the given transition line is an EPS transition
bool NFA::IsEPSTransition(string line)
{
    if (line[2] == 'E' && line[3] == 'P' && line[4] == 'S')
    {
        return true;
    }

    return false;
}
