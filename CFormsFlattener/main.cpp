//
//  main.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-01-28.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include <iostream>
#include <ctime>

#include "Config.h"
#include "SubmissionProcessor.h"
#include "MySQLDataProvider.h"

using namespace std;

static const unsigned int PAGE_SIZE = 1000;

void printUsage(string executableName);

// sample usage: app <settings_file> <form_name> <output_file>
int main(int argc, const char * argv[])
{
    if (argc != 4) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }
    
    string configFile = argv[1];
    string formId = argv[2];
    string outputFile = argv[3];
    
    Config config(configFile);
    MySQLDataProvider provider(formId, &config);
    SubmissionProcessor processor(&provider, PAGE_SIZE);
    
    time_t start;
    time_t end;
    
    time(&start);
    cout << "Processing entries..." << endl;
    processor.writeToFile(outputFile);
    cout << "CSV Data written to " << outputFile << endl;
    time(&end);
    
    double seconds = difftime(end, start);
    cout << "Process completed in " << seconds << " seconds." << endl;
    
    return EXIT_SUCCESS;
}

void printUsage(string executableName)
{
    cout << "Wrong number of arguments!" << endl;
    cout << "Usage: " << executableName << " <config_file> <cform_id> <output_file>" << endl;
}