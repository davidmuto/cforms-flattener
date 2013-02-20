//
//  Config.h
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-20.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#ifndef __CFormsFlattener__Config__
#define __CFormsFlattener__Config__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Config {
public:
    Config(string filePath) {
        ifstream file;
        string line;
        file.open(filePath);
        
        short index = 0;
        while(!file.eof()) {
            getline(file, line);
            this->setValue(index++, line);
        }
        
        file.close();
    }

    void setValue(short lineIndex, string value) {
        switch (lineIndex) {
            case 0: this->host = value; break;
            case 1: this->user = value; break;
            case 2: this->password = value; break;
            case 3: this->catalog = value; break;
        }
    }
    
    /* Simple accessors */
    string getHost() { return this->host; }
    string getUser() { return this->user; }
    string getPassword() { return this->password; }
    string getCatalog() { return this->catalog; }
    
private:
    string host, user, password, catalog;
};

#endif /* defined(__CFormsFlattener__Config__) */
