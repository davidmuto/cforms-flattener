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
    MySQLDataProvider(string formId, Config *config);
    ~MySQLDataProvider();
    
    virtual vector<string> getAllFieldNames();
    virtual unsigned int getNumberOfSubmissions();
    virtual Submission *loadSubmissions(unsigned int offset, unsigned int limit, unsigned int &numSubmissions);
    virtual void loadSubmissionData(Submission *submissions, unsigned int numSubmissions);
    
private:
    string submissionTable, dataTable;
};

#endif /* defined(__CFormsFlattener__MySQLDataProvider__) */
