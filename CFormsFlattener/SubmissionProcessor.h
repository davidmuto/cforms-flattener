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
    SubmissionProcessor(CFormsDataProvider *provider, unsigned int pageSize);
    ~SubmissionProcessor();
    
    void writeToFile(string outputFileName);
    
private:
    CFormsDataProvider *provider;
    unsigned int numSubmissions;
    unsigned int pageSize;
};

#endif /* defined(__CFormsFlattener__SubmissionProcessor__) */
