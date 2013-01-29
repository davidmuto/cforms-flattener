//
//  FormRecord.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-01-28.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "FormRecord.h"

FormRecord::FormRecord()
{
    // initialize field map
    this->fields = map<string,string>();
}

FormRecord::~FormRecord()
{
    // destructor
}

void FormRecord::setId(unsigned int id)
{
    this->id = id;
}

void FormRecord::setDate(time_t date)
{
    this->date = date;
}

void FormRecord::setEmail(string email)
{
    this->email = email;
}

void FormRecord::addFieldValue(string fieldName, string fieldValue)
{
    this->fields[fieldName] = fieldValue;
}

unsigned int FormRecord::getId()
{
    return this->id;
}

time_t FormRecord::getDate()
{
    return this->date;
}

string FormRecord::getEmail()
{
    return this->getEmail();
}

string FormRecord::getFieldValue(string fieldName)
{
    return this->fields[fieldName];
}