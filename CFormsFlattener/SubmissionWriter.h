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
    SubmissionWriter(string outputFile) {
        this->outputFile = outputFile;
    }
    
    void writeFieldNames(vector<string> &fieldNames);
    void writeToFile(Submission *submissions, vector<string> &fieldNames, unsigned int numRecords);
    
private:
    string outputFile;
};

#endif /* defined(__CFormsFlattener__SubmissionWriter__) */
