//
//  CFormsDataProvider.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-18.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef CFormsFlattener_CFormsDataProvider_h
#define CFormsFlattener_CFormsDataProvider_h

#include "Submission.h"
#include "Config.h"

struct submissionDataT {
    unsigned int submissionId;
    string fieldName;
    string fieldValue;
};

class CFormsDataProvider {
public:
    CFormsDataProvider(string formId, Config *config) {
        this->formId = formId;
        this->config = config;
    }
    
    string getFormId() { return this->formId; }
    Config *getConfig() { return this->config; }
    
    /* abstract methods */
    virtual vector<string> getAllFieldNames() = 0;
    virtual unsigned int getNumberOfSubmissions() = 0;
    virtual Submission *loadSubmissions(unsigned int offset, unsigned int limit, unsigned int &numSubmissions) = 0;
    virtual void loadSubmissionData(Submission *submissions, unsigned int numSubmissions) = 0;
    
private:
    string formId;
    Config *config;
};

#endif
