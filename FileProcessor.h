/*
# Name: Mark Griffin
# ID Number: 2340502
# Email: magriffin@chapman.edu
# Course: CPSC406-01
# Assignment: Course Project
*/

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileProcessor
{
    public:
        // Constructor, Deconstructor
        FileProcessor();
        ~FileProcessor();

        void processFile(string inputFile, string outputFile);

    private:
        // Helper methods
        void openFile(string fileName, bool isInput);
        void readInputFile();
        void closeFile(string fileName, bool isInput);
        void writeOutputFile();

        // Members Variables
        ifstream inputStream;
        ofstream outputStream;
        string NFA;
        string DFA;
};

#endif