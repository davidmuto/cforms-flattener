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
    this->fields = map<string,string>();
}

FormRecord::~FormRecord()
{
    // destructor
}