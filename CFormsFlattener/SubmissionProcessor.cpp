//
//  SubmissionProcessor.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-18.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "SubmissionProcessor.h"
#include "SubmissionWriter.h"
#include <cmath>
#include <iostream>

SubmissionProcessor::SubmissionProcessor(CFormsDataProvider *provider, unsigned int pageSize)
{
    this->provider = provider;
    this->numSubmissions = 0;
    this->pageSize = pageSize;
}

SubmissionProcessor::~SubmissionProcessor()
{
    
}

void SubmissionProcessor::writeToFile(string outputFileName)
{
    SubmissionWriter writer(outputFileName);
    
    unsigned int totalNumRecords = this->provider->getNumberOfSubmissions();
    unsigned int numPages = ceil(totalNumRecords * 1.0 / pageSize * 1.0);
    
    cout << "Collecting all custom fields..." << endl;
    vector<string> fields = this->provider->getAllFieldNames();
    writer.writeFieldNames(fields);
    
    unsigned int numRecordsInPage;
    
    for (int i = 0; i < numPages; i++) {
        cout << "Processing page " << (i + 1) <<" of " << numPages << "...";
        
        // load records and fill custom fields
        Submission *records = this->provider->loadSubmissions(i * this->pageSize, this->pageSize, numRecordsInPage);
        this->provider->loadSubmissionData(records, numRecordsInPage);
        
        // write to output file
        cout << "written." << endl;
        writer.writeToFile(records, fields, numRecordsInPage);
        
        // clean up
        delete [] records;
        records = NULL;
    }
}

// performs a bisection search: assumes submissions are ordered by id ascending
static Submission *findById(unsigned int id, Submission *submissions, unsigned int numRecords)
{
    unsigned int min = 0;
    unsigned int max = numRecords;
    unsigned int mid = 0;
    
    Submission *found = NULL;
    Submission *current = NULL;
    
    while (min <= max) {
        mid = (min + max) / 2;
        current = &submissions[mid];
        
        // found it!
        if (current->getId() == id) {
            found = current;
            break;
        }
        
        // cut search space in half
        if (id < current->getId()) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }
    
    return found;
}

static int compareSubmissions(const void *p1, const void *p2)
{
    Submission *sub1 = (Submission *)p1;
    Submission *sub2 = (Submission *)p2;
    
    // ascending order
    return sub1->getId() - sub2->getId();
}