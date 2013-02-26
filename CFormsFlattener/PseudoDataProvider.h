//
//  PseudoDataProvider.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__PseudoDataProvider__
#define __CFormsFlattener__PseudoDataProvider__

#include "CFormsDataProvider.h"

class PseudoDataProvider : public CFormsDataProvider {
public:
    PseudoDataProvider(string formId) : CFormsDataProvider(formId, NULL) { }
    
    virtual vector<string> getAllFieldNames();
    virtual unsigned int getNumberOfSubmissions();
    virtual Submission *loadSubmissions(unsigned int offset, unsigned int limit, unsigned int &numSubmissions);
    virtual void loadSubmissionData(Submission *submissions, unsigned int numSubmissions);
};

#endif /* defined(__CFormsFlattener__PseudoDataProvider__) */
