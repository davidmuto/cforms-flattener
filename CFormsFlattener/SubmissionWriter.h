//
//  SubmissionWriter.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__SubmissionWriter__
#define __CFormsFlattener__SubmissionWriter__

#include "Submission.h"

class SubmissionWriter {
public:
    SubmissionWriter(Submission *submissions, unsigned int numRecords) {
        this->records = submissions;
        this->numRecords = numRecords;
    }
    
    void writeToFile(string fileName);
    
private:
    Submission *records;
    unsigned int numRecords;
};

#endif /* defined(__CFormsFlattener__SubmissionWriter__) */
