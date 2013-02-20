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
    MySQLDataProvider(string formId, Config *config) : CFormsDataProvider(formId, config) {
        this->submissionTable = config->getTablePrefix() + "cformssubmissions";
        this->dataTable = config->getTablePrefix() + "cformsdata";
    }
    
    virtual Submission *loadSubmissions(unsigned int &numSubmissions);
    virtual submissionDataT *loadSubmissionData(unsigned int &numSubmissions);
    
private:
    string submissionTable, dataTable;
};

#endif /* defined(__CFormsFlattener__MySQLDataProvider__) */
