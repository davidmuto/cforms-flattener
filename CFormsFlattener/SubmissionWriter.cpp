//
//  SubmissionWriter.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "SubmissionWriter.h"

#include <fstream>
#include <iostream>

static string timeString(time_t time)
{
    char buffer[32];
    strftime(buffer, 32, "%Y%m%d%H%M%S", gmtime(&time));
    
    return string(buffer);
}

static void writeSubmissionRecord(ofstream &fs, vector<string> &fieldNames, Submission &record)
{
    fs << record.getId() << ",";
    fs << "\"" + record.getFormId() << "\",";
    fs << "\"" + record.getEmail() << "\",";
    fs << "\"" + record.getIP() << "\",";
    fs << timeString(record.getDate());
    
    for (int j = 0; j < fieldNames.size(); j++) {
        fs << ",\"" << record.getField(fieldNames[j]) << "\"";
    }
    
    fs << endl;
}

void SubmissionWriter::writeFieldNames(vector<string> &fieldNames)
{
    ofstream fs;
    fs.open(this->outputFile.c_str());
    fs << "id,formId,email,ip,date";
    
    for (int i = 0; i < fieldNames.size(); i++) {
        fs << ",\"" << fieldNames[i] << "\"";
    }
    
    fs << endl;
    fs.close();
}

void SubmissionWriter::writeToFile(Submission *submissions, vector<string> &fieldNames, unsigned int numRecords)
{
    ofstream fs;
    fs.open(this->outputFile.c_str(), ios::out|ios::app);
    
    for (unsigned int i = 0; i < numRecords; i++) {
        writeSubmissionRecord(fs, fieldNames, submissions[i]);
    }
    
    fs.close();
}
