//
//  MySQLDataProvider.cpp
//  CFormsFlattener
//
//  Created by David Muto on 2013-02-19.
//  Copyright (c) 2013 David Muto. All rights reserved.
//

#include "MySQLDataProvider.h"

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

static sql::Connection *getConnection(Config *config)
{
    sql::Driver *driver = get_driver_instance();
    sql::Connection *conn = driver->connect(config->getHost(), config->getUser(), config->getPassword());
    conn->setSchema(config->getCatalog());
    
    return conn;
}

Submission *MySQLDataProvider::loadSubmissions(unsigned int &numSubmissions)
{
    sql::Connection *conn = getConnection(this->getConfig());
    sql::Statement *stmt = conn->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM wp_cformssubmissions");
    
    unsigned int count = 0;
    
    while (res->next()) {
        count++;
    }
    
    delete res;
    delete stmt;
    delete conn;
    
    numSubmissions = count;
    return NULL;
}

submissionDataT *MySQLDataProvider::loadSubmissionData(unsigned int &numSubmissions)
{
    numSubmissions = 0;
    return NULL;
}