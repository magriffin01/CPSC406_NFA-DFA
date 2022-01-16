/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "FileProcessor.h"
#include "Parser.h"

using namespace std;

int main(int argc, char **argv)
{
    Parser parser;
    parser.parseNFAFile("{1}	{2}	{3}\na	b\n{2}\n{3}\n");
    // if (argc != 2)
    // {
    //     cout << "Usage: ./courseproject <inputFile>" << "\n";
    //     return -1;
    // }
    
    // FileProcessor *fileProcessor = new FileProcessor();
    // fileProcessor->processFile(argv[1], "result.dfa");

    // delete fileProcessor;
    return 0;
}