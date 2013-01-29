//
//  CFormsDataSource.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-01-29.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__CFormsDataSource__
#define __CFormsFlattener__CFormsDataSource__

#include "FormRecord.h"
#include <string>

class CFormsDataSource {
public:
    CFormsDataSource(std::string formName) {
        this->formName = formName;
    }
    
    void setFormName(std::string formName) {
        this->formName = formName;
    }
    
    std::string getFormName() {
        return this->formName;
    }
    
    virtual FormRecord *getRecords(int &numResults) = 0;
private:
    std::string formName;
};

#endif /* defined(__CFormsFlattener__CFormsDataSource__) */
