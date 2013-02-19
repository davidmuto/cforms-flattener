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

struct submissionDataT {
    unsigned int submissionId;
    string fieldName;
    string fieldValue;
};

class CFormsDataProvider {
public:
    CFormsDataProvider(string formId) { this->formId = formId; }
    
    string getFormId() { return this->formId; }
    
    /* abstract methods */
    virtual Submission *loadSubmissions(unsigned int &numSubmissions) = 0;
    
    // a lot of efficiency can be gained by ordering the records by submissionId
    virtual submissionDataT *loadSubmissionData(unsigned int &numSubmissions) = 0;
    
private:
    string formId;
};

#endif
