//
//  main.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-01-28.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include <iostream>
#include "SubmissionProcessor.h"
#include "PseudoDataProvider.h"

using namespace std;

// sample usage: app <settings_file> <form_name>
int main(int argc, const char * argv[])
{
    PseudoDataProvider provider("someid");
    SubmissionProcessor processor(&provider);
    
    Submission *records = processor.getSubmissions();
    
    for (int i = 0; i < processor.getNumberOfSubmissions(); i++) {
        cout << "Found Record: " << records[i].getId() << " With Id: " << records[i].getField("Id") << " and Name: " << records[i].getField("Name") << endl;
    }
    
    cout << "Loaded " << processor.getNumberOfSubmissions() << " records." << endl;
    return EXIT_SUCCESS;
}

