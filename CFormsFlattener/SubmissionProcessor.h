//
//  SubmissionProcessor.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-18.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__SubmissionProcessor__
#define __CFormsFlattener__SubmissionProcessor__

#include <vector>
#include "CFormsDataProvider.h"

class SubmissionProcessor {
public:
    SubmissionProcessor(CFormsDataProvider *provider);
    ~SubmissionProcessor();
    
    string getFormId() { return this->provider->getFormId(); }
    unsigned int getNumberOfSubmissions() { return this->numSubmissions; }
    
    Submission *getSubmissions();
    
private:
    CFormsDataProvider *provider;
    Submission *submissions;
    unsigned int numSubmissions;
    
    void loadSubmissions();
    void loadSubmissionData();
};

#endif /* defined(__CFormsFlattener__SubmissionProcessor__) */
