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

#include <iostream>

static sql::Connection *getConnection(Config *config)
{
    string host = config->getHost();
    string user = config->getUser();
    string pass = config->getPassword();
    
    sql::Driver *driver = get_driver_instance();
    sql::Connection *conn = driver->connect(host, user, pass);
    conn->setSchema(config->getCatalog());
    
    return conn;
}

static string makeSubmissionQuery(const string &fields, const string &tableName, const string &formId)
{
    return "SELECT " + fields + " FROM " + tableName +" WHERE form_id ='" + formId +"'";
}

static unsigned int countRecords(sql::Statement *stmt, const string &tableName, const string &formId)
{
    string query = makeSubmissionQuery("COUNT(*)", tableName, formId);
    sql::ResultSet *countRes = stmt->executeQuery(query);
    
    unsigned int count = 0;
    if (countRes->next()) {
        count = countRes->getUInt(1);
    }
    
    delete countRes;
    return count;
}

Submission *MySQLDataProvider::loadSubmissions(unsigned int &numSubmissions)
{
    sql::Connection *conn = getConnection(this->getConfig());
    sql::Statement *stmt = conn->createStatement();
    
    numSubmissions = countRecords(stmt, this->submissionTable, this->getFormId());
    Submission *records = new Submission[numSubmissions];
    
    string query = "SELECT id, email, unix_timestamp(sub_date), ip FROM " + this->submissionTable +" WHERE form_id = '" + this->getFormId() +"'";
    sql::ResultSet *res = stmt->executeQuery(query);
    
    unsigned int index = 0;
    while (res->next()) {
        records[index].setId(res->getUInt(1));
        records[index].setFormId(this->getFormId());
        records[index].setEmail(res->getString(2));
        records[index].setDate(time_t(res->getUInt(3)));
        records[index].setIP(res->getString(4));
        index++;
    }
    
    delete res;
    delete stmt;
    delete conn;
    
    return records;
}

submissionDataT *MySQLDataProvider::loadSubmissionData(unsigned int &numSubmissions)
{
    numSubmissions = 0;
    string whereClause = " WHERE sub_id IN (SELECT id FROM " + this->submissionTable +" WHERE form_id = '" + this->getFormId() + "')";
    
    sql::Connection *conn = getConnection(this->getConfig());
    sql::Statement *stmt = conn->createStatement();
    
    sql::ResultSet *countRes = stmt->executeQuery("SELECT COUNT(f_id) FROM " + this->dataTable + whereClause);
    if(countRes->next()) {
        numSubmissions = countRes->getUInt(1);
    }
    delete countRes;
    
    submissionDataT *records = new submissionDataT[numSubmissions];
    
    if (numSubmissions > 0) {
        sql::ResultSet *res = stmt->executeQuery("SELECT sub_id, field_name, field_val FROM " + this->dataTable + whereClause);

        unsigned int index = 0;
        while (res->next()) {
            records[index].submissionId = res->getUInt(1);
            records[index].fieldName = res->getString(2);
            records[index].fieldValue = res->getString(3);
            index++;
        }
        
        delete res;
    }
    
    return records;
}