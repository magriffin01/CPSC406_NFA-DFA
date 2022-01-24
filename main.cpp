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
    if (argc != 2)
    {
        cout << "Usage: ./courseproject <inputFile>" << "\n";
        return -1;
    }
    
    FileProcessor *fileProcessor = new FileProcessor();
    fileProcessor->ProcessInput(argv[1]);
    Parser *parser = new Parser();
    parser->parseNFAFile(fileProcessor->GetNFAInput());
    NFA *nfa = new NFA(*parser);
    nfa->ConstructNFA();
    DFA *dfa = new DFA(nfa);
    dfa->ConvertFromNFA();
    dfa->ToString();
    fileProcessor->WriteToFile("resultDFA.dfa", dfa->GetDFA());

    delete fileProcessor;
    delete parser;
    delete nfa;
    delete dfa;

    return 0;
}