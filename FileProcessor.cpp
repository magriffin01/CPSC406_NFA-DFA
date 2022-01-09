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

// Takes in an input file and output file, reads the input file, and writes the output file
void FileProcessor::processFile(string inputFile, string outputFile)
{
    openFile(inputFile, true);
    readInputFile();
    closeFile(inputFile, true);
    openFile(outputFile, false);
    writeOutputFile();
    closeFile(outputFile, false);
}

// Reads the NFA from the input file
void FileProcessor::readInputFile()
{
    string line;
    
    // TODO: Delete later
    DFA = "";

    getline(inputStream, line);

    while (!inputStream.fail())
    {
        //TODO: Temporary code that just prints out each character, implement actual parsing the input next
        // for (int i = 0; i < line.length(); ++i)
        // {
        //     if (line.at(i) == '\t')
        //     {
        //         cout << "Tab character found";
        //     }

        //     cout << line.at(i) << "\n";
        // }

        DFA = DFA + line + "\n";

        getline(inputStream, line);
    }

    if (!inputStream.eof())
    {
        cout << "Input failure before reaching end of th file." << "\n";
    }

    cout << DFA;
}

// Writes the resulting DFA to the output file
void FileProcessor::writeOutputFile()
{
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