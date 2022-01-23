/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "NFA.h"

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

    // TODO: Delete Once Complete
    for (int i = 0; i < states.size(); ++i)
    {
        cout << "States Left: " << states[i]->GetStateName() << '\n';
    }

    for (int i = 0; i < acceptStates.size(); ++i)
    {
        cout << "Accept States Left: " << acceptStates[i]->GetStateName() << '\n';
    }
}

// Builds the NFA resulting from the work the parser has done on the file
void NFA::ConstructNFA()
{
    cout << "\n" << "Constructing NFA: " << "\n";
    BuildStates();
    SetAlphabet();
    SetStartState();
    SetAcceptStates();
    SetTransitions();
    // Make states for each state
    // Set the alphabet
    // Set the start state
    // Set the accept states
    // Fill in the transitions
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

    // TODO: Delete once complete
    // For testing only
    for (int i = 0; i < states.size(); ++i)
    {
        cout << "State: " << states[i]->GetStateName() << '\n';
    }
}

// Sets the alphabet in the NFA
void NFA::SetAlphabet()
{
    alphabet = parser.GetParsedAlphabet();

    // TODO: Delete once complete
    // For testing only
    for (int i = 0; i < alphabet.size(); ++i)
    {
        cout << "Symbol: " << alphabet[i] << '\n';
    }
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
            return;
        }
    }

    // TODO: Delete once complete
    // For testing only
    cout << "Start State: " << startState->GetStateName() << '\n';
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

    // TODO: Delete once complete
    // For testing only
    for (int i = 0; i < acceptStates.size(); ++i)
    {
        cout << "Accept State: " << acceptStates[i]->GetStateName() << '\n';
    }
}

// Fills in the transition hash map in each of the states
void NFA::SetTransitions()
{
    // Get the state name from the parser
    // Insert the transitions in the states
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

    // TODO: Delete once complete
    // For testing only
    for (int i = 0; i < states.size(); ++i)
    {
        cout << "State: " << states[i]->GetStateName() << '\n';
        states[i]->DisplayTransitionStates();
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