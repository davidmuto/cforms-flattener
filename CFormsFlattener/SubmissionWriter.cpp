//
//  SubmissionWriter.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "SubmissionWriter.h"
#include <sstream>

#include <fstream>
#include <iostream>

static string getLargestNumberOfFieldsString(Submission *submissions, unsigned int numRecords)
{
    string fields = "";
    string currentFields = "";
    
    for (int i = 0; i < numRecords; i++) {
        currentFields = submissions[i].getCSVAttributeString();
        if (currentFields.size() > fields.size()) {
            fields = currentFields;
        }
    }
    
    return fields;
}

static vector<string> split(const string &s, char delimeter)
{
    vector<string> tokens;
    stringstream ss(s);
    string token;
    
    while (getline(ss, token, delimeter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

static void writeFieldNames(ostringstream &ss, vector<string> &fieldNames)
{
    ss << "id,formId,email,ip,date";
    for (int j = 0; j < fieldNames.size(); j++) {
        ss << ",\"" << fieldNames[j] << "\"";
    }
    ss << endl;
}

static string timeString(time_t time)
{
    char buffer[32];
    strftime(buffer, 32, "%Y%m%d%H%M%S", gmtime(&time));
    
    return string(buffer);
}

static void writeSubmissionRecord(ostringstream &ss, vector<string> &fieldNames, Submission &record)
{
    ss << record.getId() << ",";
    ss << "\"" + record.getFormId() << "\",";
    ss << "\"" + record.getEmail() << "\",";
    ss << "\"" + record.getIP() << "\",";
    ss << timeString(record.getDate());
    
    for (int j = 0; j < fieldNames.size(); j++) {
        ss << ",\"" << record.getField(fieldNames[j]) << "\"";
    }
    
    ss << endl;
}

void SubmissionWriter::writeToFile(string fileName)
{
    ostringstream ss;
    vector<string> fieldNames = split(getLargestNumberOfFieldsString(this->records, this->numRecords), ',');
    
    writeFieldNames(ss, fieldNames);
    for (int i = 0; i < this->numRecords; i++) {
        writeSubmissionRecord(ss, fieldNames, this->records[i]);
    }
    
    ofstream outputFile;
    outputFile.open(fileName.c_str());
    outputFile << ss.str();
    outputFile.close();
}