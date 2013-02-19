//
//  Submission.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-18.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__Submission__
#define __CFormsFlattener__Submission__

#include <string>
#include <map>
#include <vector>

using namespace std;

class Submission {
public:
    Submission();
    
    string getCSVAttributeString();
    string getCSVDataString(vector<string> &fieldNames);
    
    
    /* Simple accessors */
    unsigned int getId() { return this->id; }
    string getFormId() { return this->formId; }
    string getEmail() { return this->email; }
    string getIP() { return this->ip; }
    time_t getDate() { return this->date; }
    
    /* Simple mutators */
    void setId(unsigned int id) { this->id = id; }
    void setFormId(string formId) { this->formId = formId; }
    void setEmail(string email) { this->email = email; }
    void setIP(string ip) { this->ip = ip; }
    void setDate(time_t date) { this->date = date; }
    
    string getField(string fieldName);
    void setField(string fieldName, string fieldValue);
    
private:
    unsigned int id;
    string formId;
    string email;
    string ip;
    time_t date;
    map<string,string> fields;
};

#endif /* defined(__CFormsFlattener__Submission__) */
