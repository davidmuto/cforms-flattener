//
//  Submission.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-18.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "Submission.h"

Submission::Submission()
{
    this->id = 0;
    this->formId = "";
    this->email = "";
    this->ip = "";
    this->date = 0;
}

static void lcase(string &str)
{
    std:transform(str.begin(), str.end(), str.begin(), std::tolower);
}

string Submission::getCSVAttributeString()
{
    map<string,string>::const_iterator current;
    string csvLine = "";
    
    for (current = this->fields.begin(); current != this->fields.end(); current++) {
        // add the field name to the string
        if (current != this->fields.begin()) csvLine += ",";
        csvLine += current->first;
    }
    
    return csvLine;
}

vector<string> Submission::getFieldNames()
{
    vector<string> names;
    
    map<string, string>::const_iterator current;
    for (current = this->fields.begin(); current != this->fields.end(); current++) {
        names.push_back(current->first);
    }
    
    return names;
}

string Submission::getField(string fieldName)
{
    lcase(fieldName);
    return this->fields[fieldName];
}

void Submission::setField(string fieldName, string fieldValue)
{
    lcase(fieldName);
    this->fields[fieldName] = fieldValue;
}