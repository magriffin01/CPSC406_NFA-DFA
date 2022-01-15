/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "FileProcessor.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: ./courseproject <inputFile>" << "\n";
        return -1;
    }
    
    FileProcessor *fileProcessor = new FileProcessor();
    fileProcessor->processFile(argv[1], "result.dfa");

    delete fileProcessor;
    return 0;
}