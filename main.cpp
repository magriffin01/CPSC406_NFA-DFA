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

using namespace std;

int main(int argc, char **argv)
{
    Parser parser;
    parser.parseNFAFile("{1}	{2}	{3}\na	b\n{2}\n{3}\n{1}, a  = {3}\n{1}, b  = {2}\n{2}, a = {1}\n{2}, a = {2}\n{2}, b EP = {3}\n{3}, b = {1}"); // 
    // if (argc != 2)
    // {
    //     cout << "Usage: ./courseproject <inputFile>" << "\n";
    //     return -1;
    // }
    
    // FileProcessor *fileProcessor = new FileProcessor();
    // fileProcessor->processFile(argv[1], "result.dfa");

    // delete fileProcessor;

    State testState1;
    State testState2;
    State testState3;

    testState1.SetStateName('1');
    testState2.SetStateName('2');
    testState3.SetStateName('3');

    vector<State> a1;
    a1.push_back(testState3);
    vector<State> b1;
    b1.push_back(testState2);
    
    testState1.InsertTransition("a", a1);
    testState1.InsertTransition("b", b1);

    testState1.DisplayTransitionStates();

    return 0;
}