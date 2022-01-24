/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "DFA.h"

DFA::DFA()
{

}

DFA::DFA(NFA* nfa)
{
    this->nfa = nfa;
    this->alphabet = nfa->GetAlphabet();
}

DFA::~DFA()
{
    for (int i = 0; i < states.size(); ++i)
    {
        delete states[i];
    }
}

// Returns the DFA string
string DFA::GetDFA()
{
    return dfa;
}

// Converts NFA to DFA
void DFA::ConvertFromNFA()
{
    // Epsilon Closure the start state from NFA
    // From start state, look at all possible transitions on the alphabet and find new states
    // Once there are no new states, done
    // Set Accept States
    cout << "Constructing DFA" << '\n';
    // Set all Epsilon Closures
    // Set Start State
    // Calculate Remaining States
        // Loop until an index is greater than states.size
        // Check each state on each letter
        // If a new state is made, push to states
        // Add the transitions
    // Set accept states
    SetStartState();
    CalculateRemainingStates();

    cout << "STATES IN CONSTRUCTION: " << '\n';
    for (int row = 0; row < statesInConstruction.size(); ++row)
    {
        for (int column = 0; column < statesInConstruction[row].size(); ++column)
        {
            cout << "ROW: " << row << " COLUMN: " << column << '\n';
            cout << "STATE: " << statesInConstruction[row][column]->GetStateName() << '\n';
        }
    }

    cout << "COMBINED STATES: " << '\n';
    for (int i = 0; i < states.size(); ++i)
    {
        cout << "State: " << states[i]->GetCombinedStateName() << '\n';
    }

    for (int i = 0; i < states.size(); ++i)
    {
        cout << "State Name: " << states[i]->GetCombinedStateName() << '\n';
        states[i]->DisplayTransitionStates();
    }
}

// Converts DFA to string
void DFA::ToString()
{
    MakeDFAString();
}

// Sets the start state
void DFA::SetStartState()
{
    vector<State*> newStartStates; // Placeholder vector to get the epsilon closure
    nfa->EpsilonClosure(nfa->GetStartState(), newStartStates);
    sort(newStartStates.begin(), newStartStates.end()); // Sort in ascending order

    statesInConstruction.push_back(newStartStates);

    string newName = ",";
    bool isAcceptState = false;

    for (int i = 0; i < newStartStates.size(); ++i)
    {
        if (newStartStates[i]->GetIsAcceptState()) // If any of these states are accept states, the new state is an accept state
        {
            isAcceptState = true;
        }

        newName = newName + newStartStates[i]->GetStateName() + ",";
    }

    startState = new State();
    startState->SetCombinedStateName(newName);
    startState->SetIsAcceptState(isAcceptState);

    if (isAcceptState)
    {
        acceptStates.push_back(startState);
    }

    states.push_back(startState);

    // TODO: Delete once complete
    cout << "Start State: " << startState->GetCombinedStateName() << '\n';
}

// Calculates the Remaining States
void DFA::CalculateRemainingStates()
{
    int index = 0; // Index used to see if we are bigger than states.size() (i.e. we have no more states to process)
    State* currentCombinedState; // Current combined state (new state in the DFA)
    State* currentStateInConstruction; // State we are looking at in Construction
    vector<State*> currentTransitions; // Transitions from a single NFA state
    vector<State*> currentEpsilonTransitions; // Epsilon transitions that exist on the new transitions
    vector<State*> newTransitions; // Transitions from a new state, to other new states
    State* newState; // State to build
    string newStateName = ","; // name of the new state
    bool isNewStateAcceptState = false; // Boolean for determining if a state is an accept state
    string currentSymbol = ""; // Current Symbol in Alphabet we are on

    while (index < states.size()) // Loop on the states vector
    {
        cout << '\n' << "Index: " << index << '\n';
        currentCombinedState = states[index]; // Set the currentCombinedState
        cout << "Current Combined State: " << states[index]->GetCombinedStateName() << '\n';
        for (int symbol = 0; symbol < alphabet.size(); ++symbol) // Loop on the alphabet
        {
            currentSymbol = alphabet[symbol]; // Set the current symbol to the current symbol in the alpha
            cout << "Symbol: " << currentSymbol << '\n';

            for (int column = 0; column < statesInConstruction[index].size(); ++column) // Loop through the original NFA states
            {
                currentStateInConstruction = statesInConstruction[index][column]; // Get the current state in construction (a vector that cotnains the vector of the individual states from the nfa)
                cout << "Construct State: " << currentStateInConstruction->GetStateName() << '\n';
                currentTransitions = currentStateInConstruction->GetTransition(currentSymbol); // Get the transitions from the NFA state

                if (currentTransitions.size() == 0) // If no transitions, continue
                {
                    continue;
                }
            
                for (int i = 0; i < currentTransitions.size(); ++i) // Loop through possible transitions to add
                {
                    
                    if (find(newTransitions.begin(), newTransitions.end(), currentTransitions[i]) == newTransitions.end()) // If the transition does not already exist, add
                    {
                        cout << "Adding Transition: " << currentTransitions[i]->GetStateName() << '\n';
                        newTransitions.push_back(currentTransitions[i]);
                    }
                }

                // Check for epsilon transitions on the new transitions
                for (int i = 0; i < newTransitions.size(); ++i)
                {
                    nfa->EpsilonClosure(newTransitions[i], currentEpsilonTransitions);
                }

                // If epsilon transitions exist, check to see if that transition already exists, if not, add
                for (int i = 0; i < currentEpsilonTransitions.size(); ++i)
                {
                    
                    if (find(newTransitions.begin(), newTransitions.end(), currentEpsilonTransitions[i]) == newTransitions.end()) // If transition does not already exist, add
                    {
                        cout << "Adding EPS Transition: " << currentEpsilonTransitions[i]->GetStateName() << '\n';
                        newTransitions.push_back(currentEpsilonTransitions[i]);
                    }
                }

                currentEpsilonTransitions.clear();
            }

            sort(newTransitions.begin(), newTransitions.end());

            for (int i = 0; i < newTransitions.size(); ++i)
            {
                cout << "New Trans.: " << newTransitions[i]->GetStateName() << '\n';
            }

            if (find(statesInConstruction.begin(), statesInConstruction.end(), newTransitions) == statesInConstruction.end()) // If the vector is of new transitions is not already in states in construction, add
            {
                statesInConstruction.push_back(newTransitions);
            }

            for (int i = 0; i < newTransitions.size(); ++i) // Check to see if any of these new transitions are accept states
            {
                if (newTransitions[i]->GetIsAcceptState())
                {
                    isNewStateAcceptState = true;
                }
                newStateName = newStateName + newTransitions[i]->GetStateName() + ","; // Set the new state name
            }

            if (IsEmptyState(newStateName)) // If state name is just a comma, must be EM
            {
                newStateName = "EM";
            }

            bool isRepeatedState = false;
            for (int i = 0; i < states.size(); ++i) // Check to see if the state is repeated
            {
                if (newStateName == states[i]->GetCombinedStateName())
                {
                    cout << "Is repeated State: " << newStateName << '\n';
                    isRepeatedState = true;
                    newState = states[i];
                }
            }

            if (!isRepeatedState) // If not a repeat state, make a new state
            {
                newState = new State();
                newState->SetCombinedStateName(newStateName);
                cout << "New State: " << newStateName << '\n';
                newState->SetIsAcceptState(isNewStateAcceptState);
                if (newState->GetIsAcceptState())
                {
                    acceptStates.push_back(newState);
                }
                states.push_back(newState);
            }

            vector<State*> vecNewState; // Temporary vector to add new state to to use InsertTransition
            vecNewState.push_back(newState);
            currentCombinedState->InsertTransition(currentSymbol, vecNewState);

            newStateName = ","; // Reset state name and clear new transitions
            newTransitions.clear();
            isNewStateAcceptState = false;
        }

        ++index; // go to the next element in the states vector
    }
}

// Returns whether the given state name is an empty state or not
bool DFA::IsEmptyState(string stateName)
{
    if (stateName == ",")
    {
        return true;
    }

    return false;
}

// Converts the DFA to a string
void DFA::MakeDFAString()
{
    string listOfStates;
    string listOfSymbols;
    string startStateName;
    string setOfValidAcceptStates;
    string transitionFunction;

    listOfStates = GetListOfStates();
    listOfSymbols = GetListOfSymbols();
    startStateName = GetStartName();
    setOfValidAcceptStates = GetSetOfValidAcceptStates();
    transitionFunction = GetTransitionFunction();

    dfa = listOfStates + listOfSymbols + startStateName + setOfValidAcceptStates + transitionFunction;
    cout << dfa;
}

// Returns the list of states in the DFA as a string
string DFA::GetListOfStates()
{
    string result = "";

    for (int i = 0; i < states.size(); ++i) // Loop through each state
    {
        result += "{"; // State is encompassed by braces so add at beginning and at end

        string name = RemoveCommasInName(states[i]->GetCombinedStateName()); // Get the state name and check if it is empty
        result += name;
        result = result + "}" + '\t'; // Add closing brace and tab character
    }

    cout << "List of States: " << result << '\n';
    return result + '\n';
}

// Returns a string of the list of symbols
string DFA::GetListOfSymbols()
{
    string result = "";
    
    for (int i = 0; i < alphabet.size(); ++i) // Loop through alphabet
    {
        result += alphabet[i];
        result += '\t';
    }

    cout << "List of Symbols: " << result << '\n';
    return result + '\n';
}

// Returns a string of the start state name
string DFA::GetStartName()
{
    string result = "{";

    string name = RemoveCommasInName(startState->GetCombinedStateName());
    result += name;
    result = result + "}";

    cout << "Start State: " << result << '\n';
    return result + '\n';
}

// Returns a string of the valid accept states
string DFA::GetSetOfValidAcceptStates()
{
    string result = "";

    for (int i = 0; i < acceptStates.size(); ++i)
    {
        result += "{";
        string name = RemoveCommasInName(acceptStates[i]->GetCombinedStateName());
        result += name;
        result = result + "}" + '\t';
    }

    cout << "List of Accept States: " << result << '\n';
    return result + '\n';
}

// Returns the transition function as a string
string DFA::GetTransitionFunction()
{
    string result = "";

    for (int i = 0; i < states.size(); ++i)
    {
        result += "{";

        State* currentState = states[i]; // Set Temp Current State
        string name = RemoveCommasInName(currentState->GetCombinedStateName());
        result += name;
        result = result + "}, ";

        string currentSymbol;
        for (int j = 0; j < alphabet.size(); ++j) // Loop through alphabet
        {
            currentSymbol = alphabet[j];
            vector<State*> transition = currentState->GetTransition(currentSymbol); // Get the transition for that symbol

            result = result + currentSymbol + " = {" + RemoveCommasInName(transition[0]->GetCombinedStateName()) + "}\n"; // Add the transition part to the string
            if (j + 1 < alphabet.size()) // If this is not the last time through the alphabet, add the braces and name of the state again
            {
                result = result + "{" + name + "}, ";
            } 

        }
        
    }

    cout << "Transition Function: " << '\n' << result << '\n';
    return result + '\n';
}

// Removes the excess commas in a state name
string DFA::RemoveCommasInName(string name)
{
    string result;
    for (int i = 0; i < name.length(); ++i)
    {
        if (name.at(i) == ',')
        {
            continue;
        }

        result += name.at(i);

        if (i + 2 < name.length())
        {
            result += ", ";
        }
    }

    return result;
}
