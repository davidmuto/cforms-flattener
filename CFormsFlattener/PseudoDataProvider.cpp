//
//  PseudoDataProvider.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "PseudoDataProvider.h"
#include <sstream>

static const int NUM_RECORDS = 100000;

static string numToString (int num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

vector<string> PseudoDataProvider::getAllFieldNames()
{
    vector<string> names;
    names.push_back("Id");
    names.push_back("Name");
    
    return names;
}

unsigned int PseudoDataProvider::getNumberOfSubmissions()
{
    return NUM_RECORDS;
}

Submission *PseudoDataProvider::loadSubmissions(unsigned int offset, unsigned int limit, unsigned int &numSubmissions)
{
    Submission *records = new Submission[NUM_RECORDS];
    numSubmissions = NUM_RECORDS;
    
    for (int i = 0; i < NUM_RECORDS; i++) {
        records[i].setId(i);
    }
    
    return records;
}

void PseudoDataProvider::loadSubmissionData(Submission *submissions, unsigned int numSubmissions)
{
    numSubmissions = NUM_RECORDS * 2;
    submissionDataT *records = new submissionDataT[numSubmissions];
    
    unsigned int subId = 0;
    
    for (int i = 0; i < numSubmissions; i+=2) {
        records[i].submissionId = subId;
        records[i].fieldName = "Id";
        records[i].fieldValue = numToString(subId);
        
        records[i+1].submissionId = subId;
        records[i+1].fieldName = "Name";
        records[i+1].fieldValue = "User " + numToString(subId);
        
        subId++;
    }
    delete records;
    //return records;
}