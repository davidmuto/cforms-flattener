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
    
    // properties
    void setId(unsigned int id);
    void setDate(time_t date);
    void setEmail(string email);
    void addFieldValue(string fieldName, string fieldValue);
    
    unsigned int getId();
    time_t getDate();
    string getEmail();
    string getFieldValue(string fieldName);
    
private:
    unsigned int id;
    time_t date;
    string email;
    map<string,string> fields;
};

#endif /* defined(__CFormsFlattener__FormRecord__) */
