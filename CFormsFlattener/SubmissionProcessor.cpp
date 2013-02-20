//
//  SubmissionProcessor.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-18.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "SubmissionProcessor.h"
#include <stdlib.h>
#include <iostream>

SubmissionProcessor::SubmissionProcessor(CFormsDataProvider *provider)
{
    this->provider = provider;
    this->submissions = NULL;
    this->numSubmissions = 0;
}

SubmissionProcessor::~SubmissionProcessor()
{
    // delete heap allocated objects
    if(this->submissions != NULL) {
        delete [] this->submissions;
    }
}

Submission *SubmissionProcessor::getSubmissions()
{
    if (this->submissions == NULL) {
        this->loadSubmissions();
        this->loadSubmissionData();
    }
    
    return this->submissions;
}

/*
 Private Implementation
 */


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

static int compareSubmissions(const void *p1, const void *p2) {
    Submission *sub1 = (Submission *)p1;
    Submission *sub2 = (Submission *)p2;
    
    // ascending order
    return sub1->getId() - sub2->getId();
}

void SubmissionProcessor::loadSubmissions()
{
    if(this->submissions == NULL) {
        this->submissions = this->provider->loadSubmissions(this->numSubmissions);
        
        // since we will be looking up often it's worth sorting (in place of course)
        qsort(this->submissions, this->numSubmissions, sizeof(Submission), compareSubmissions);
    }
}

void SubmissionProcessor::loadSubmissionData()
{
    unsigned int numRecords;
    Submission *current = NULL;
    submissionDataT *records = this->provider->loadSubmissionData(numRecords);
    
    for (unsigned int i = 0; i < numRecords; i++) {
        
        // only lookup if it's different or null
        if (current == NULL || current->getId() != records[i].submissionId) {
            current = findById(records[i].submissionId, this->submissions, this->numSubmissions);
        }
        
        if (current == NULL) {
            // do something here?
            cout << "Found null node id: " << records[i].submissionId << endl;
            continue;
        }
        
        current->setField(records[i].fieldName, records[i].fieldValue);
    }
    
    // free up memory
    delete [] records;
}