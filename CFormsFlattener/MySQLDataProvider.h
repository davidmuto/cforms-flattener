//
//  MySQLDataProvider.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__MySQLDataProvider__
#define __CFormsFlattener__MySQLDataProvider__

#include "CFormsDataProvider.h"

class MySQLDataProvider : public CFormsDataProvider {
public:
    MySQLDataProvider(string formId) : CFormsDataProvider(formId) { }
    
    virtual Submission *loadSubmissions(unsigned int &numSubmissions);
    virtual submissionDataT *loadSubmissionData(unsigned int &numSubmissions);
};

#endif /* defined(__CFormsFlattener__MySQLDataProvider__) */
