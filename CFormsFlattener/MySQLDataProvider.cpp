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

static sql::Connection *getConnection(const sql::SQLString &catalog)
{
    sql::Driver *driver = get_driver_instance();
    sql::Connection *conn = driver->connect("tcp://smdgwpinstance1.cr4zlvihnnh2.us-east-1.rds.amazonaws.com:13306", "wpcglobalnews", "3a2HunE@");
    conn->setSchema(catalog);
    
    return conn;
}

Submission *MySQLDataProvider::loadSubmissions(unsigned int &numSubmissions)
{
    sql::Connection *conn = getConnection("wp_contests_globalnews");
    sql::Statement *stmt = conn->createStatement();
    sql::ResultSet *res = stmt->executeQuery("SELECT * FROM cformssubmissions");
    
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