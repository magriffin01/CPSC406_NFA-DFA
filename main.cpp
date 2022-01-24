/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "FileProcessor.h"
#include "Parser.h"
#include "State.h"
#include "NFA.h"
#include "DFA.h"

using namespace std;

int main(int argc, char **argv)
{
    Parser parser;
    parser.parseNFAFile("{1}	{2}	{3}\na	b\n{2}\n{3}\n{1}, a  = {3}\n{1}, b  = {2}\n{2}, a = {1}\n{2}, a = {2}\n{2}, EPS = {3}\n{3}, b = {1}"); // 
    NFA *nfa = new NFA(parser);
    nfa->ConstructNFA();
    DFA *dfa = new DFA(nfa);
    dfa->ConvertFromNFA();

    

    Parser *parser2 = new Parser();
    parser2->parseNFAFile("{1}	{2}	{3}\na	b\n{1}\n{1}\n{1}, b = {2}\n{1}, EPS = {3}\n{2}, a = {2}\n{2}, a = {3}\n{2}, b = {3}\n{3}, a = {1}");
    NFA *nfa2 = new NFA(*parser2);
    nfa2->ConstructNFA();
    DFA *dfa2 = new DFA(nfa2);
    dfa2->ConvertFromNFA();

    delete nfa;
    delete dfa;
    delete parser2;
    delete nfa2;
    delete dfa2;

    // if (argc != 2)
    // {
    //     cout << "Usage: ./courseproject <inputFile>" << "\n";
    //     return -1;
    // }
    
    // FileProcessor *fileProcessor = new FileProcessor();
    // fileProcessor->processFile(argv[1], "result.dfa");

    // delete fileProcessor;

    // State testState1;
    // State testState2;
    // State testState3;

    // testState1.SetStateName('1');
    // testState2.SetStateName('2');
    // testState3.SetStateName('3');

    // vector<State> a1;
    // a1.push_back(testState3);
    // vector<State> b1;
    // b1.push_back(testState2);
    
    // testState1.InsertTransition("a", a1);
    // testState1.InsertTransition("b", b1);
    
    // vector<State> a2;
    // a2.push_back(testState1);
    // a2.push_back(testState2);

    // vector<State> eps2;
    // eps2.push_back(testState3);
    
    // testState2.InsertTransition("a", a2);
    // testState2.InsertTransition("EPS", eps2);

    // testState1.DisplayTransitionStates();
    // testState2.DisplayTransitionStates();

    return 0;
}