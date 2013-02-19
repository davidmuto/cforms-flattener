//
//  main.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-01-28.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include <iostream>
#include "SubmissionProcessor.h"
#include "SubmissionWriter.h"
#include "MySQLDataProvider.h"

using namespace std;

// sample usage: app <settings_file> <form_name>
int main(int argc, const char * argv[])
{
    MySQLDataProvider provider("someid");
    SubmissionProcessor processor(&provider);
    
    Submission *records = processor.getSubmissions();
    cout << "Loaded " << processor.getNumberOfSubmissions() << " records." << endl;
    
    //SubmissionWriter writer(records, processor.getNumberOfSubmissions());
    //writer.writeToFile("");
    
    return EXIT_SUCCESS;
}