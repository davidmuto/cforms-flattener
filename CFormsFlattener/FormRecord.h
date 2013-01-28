//
//  FormRecord.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-01-28.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__FormRecord__
#define __CFormsFlattener__FormRecord__

#include <map>
#include <string>

using namespace std;

class FormRecord {
public:
    FormRecord();
    ~FormRecord();
    
    // fields
    void addFieldValue(string fieldName, string fieldValue);
    string getFieldValue(string fieldName);
    
private:
    map<string,string> fields;
};

#endif /* defined(__CFormsFlattener__FormRecord__) */
