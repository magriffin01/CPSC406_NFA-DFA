/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#include "FileProcessor.h"

FileProcessor::FileProcessor()
{

}

FileProcessor::~FileProcessor()
{
    
}

// Takes in an input file and reads the input file
void FileProcessor::ProcessInput(string inputFile)
{
    openFile(inputFile, true);
    readInputFile();
    closeFile(inputFile, true);
}

// Takes in an output file and writes the output file
void FileProcessor::WriteToFile(string outputFile, string dfa)
{
    openFile(outputFile, false);
    writeOutputFile(dfa);
    closeFile(outputFile, false);
}

// Returns the NFA read from the file
string FileProcessor::GetNFAInput()
{
    return NFA;
}

// Reads the NFA from the input file
void FileProcessor::readInputFile()
{
    string line;
    
    NFA = "";

    getline(inputStream, line);

    while (!inputStream.fail())
    {
        NFA = NFA + line + "\n";

        getline(inputStream, line);
    }

    if (!inputStream.eof())
    {
        cout << "Input failure before reaching end of th file." << "\n";
    }
}

// Writes the resulting DFA to the output file
void FileProcessor::writeOutputFile(string dfa)
{
    DFA = dfa;

    outputStream << DFA << flush;
}

// Takes in a string, the file name, and a bool, whether or not the file is an input or output file, and attempts to open it
void FileProcessor::openFile(string fileName, bool isInput)
{
    cout << "Attempting to open " << fileName << "\n";

    if (isInput)
    {
        inputStream.open(fileName);

        if (!inputStream.is_open())
        {
            cout << "Failed to open " << fileName << "\n";
            return;
        }
    }
    else
    {
        outputStream.open(fileName);

        if (!outputStream.is_open())
        {
            cout << "Failed to open " << fileName << "\n";
            return;
        }
    }

    cout << "Successfully opened " << fileName << "\n";
}

// Takes in a string, the file name, and a bool, whether or not the file is an input or output file, and attempts to close it
void FileProcessor::closeFile(string fileName, bool isInput)
{
    cout << "Attemptinng to close " << fileName << "\n";

    if (isInput)
    {
        inputStream.close();

        if (inputStream.is_open())
        {
            cout << "Failed to close " << fileName << "\n";
            return;
        }
    }
    else
    {
        outputStream.close();

        if (outputStream.is_open())
        {
            cout << "Failed to close " << fileName << "\n";
            return;
        }
    }

    cout << "Successfully closed " << fileName << "\n";
}