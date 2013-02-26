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
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>

#include <sstream>
#include <iostream>

static sql::Connection *conn;
static sql::Statement *stmt;

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
    ostringstream ss;
    ss << "SELECT " << fields << " FROM " << tableName;
    ss << " WHERE form_id = '" << formId << "'";
    
    return ss.str();
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

static Submission *findById(Submission *submissions, unsigned int numRecords, unsigned int id)
{
    Submission *found = NULL;
    
    for (unsigned int i = 0; i < numRecords; i++) {
        if (submissions[i].getId() == id) {
            found = &submissions[i];
            break;
        }
    }
    
    return found;
}

MySQLDataProvider::MySQLDataProvider(string formId, Config *config) : CFormsDataProvider(formId, config)
{
    this->submissionTable = config->getTablePrefix() + "cformssubmissions";
    this->dataTable = config->getTablePrefix() + "cformsdata";
    
    // create shared connection and statement
    conn = getConnection(config);
    stmt = conn->createStatement();
}

MySQLDataProvider::~MySQLDataProvider()
{
    // cleanup connection and statement objects
    if (stmt != NULL) delete stmt;
    if (conn != NULL) delete conn;
}

vector<string> MySQLDataProvider::getAllFieldNames()
{
    vector<string> fieldNames;
    
    ostringstream query;
    query << "SELECT DISTINCT field_name FROM " << this->submissionTable;
    query << " JOIN " << this->dataTable << " ON sub_id = id";
    query << " WHERE form_id = '" << this->getFormId() << "'";
    
    sql::ResultSet *rs = stmt->executeQuery(query.str());
    while (rs->next()) {
        fieldNames.push_back(rs->getString(1));
    }
    
    delete rs;
    return fieldNames;
}

unsigned int MySQLDataProvider::getNumberOfSubmissions()
{
    unsigned int numRecords = countRecords(stmt, this->submissionTable, this->getFormId());
    return numRecords;
}

Submission *MySQLDataProvider::loadSubmissions(unsigned int offset, unsigned int limit, unsigned int &numSubmissions)
{
    ostringstream dataQuery;
    dataQuery << "SELECT id, email, unix_timestamp(sub_date), ip FROM ";
    dataQuery << this->submissionTable;
    dataQuery << " WHERE form_id = '" << this->getFormId() << "'";
    dataQuery << " LIMIT " << offset <<", " << limit;
    
    ostringstream countQuery;
    countQuery << "SELECT COUNT(*) FROM (";
    countQuery << "SELECT id FROM " << this->submissionTable;
    countQuery << " WHERE form_id = '" << this->getFormId() << "'";
    countQuery << " LIMIT " << offset << ", " << limit;
    countQuery << ") res";
    
    // HANDLE ERROR?
    sql::ResultSet *countRes = stmt->executeQuery(countQuery.str());
    countRes->next();
    numSubmissions = countRes->getUInt(1);
    delete countRes;
    
    Submission *records = new Submission[numSubmissions];
    
    sql::ResultSet *res = stmt->executeQuery(dataQuery.str());
    
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
    return records;
}

void MySQLDataProvider::loadSubmissionData(Submission *submissions, unsigned int numSubmissions)
{
    ostringstream query;
    query << "SELECT sub_id, field_name, field_val FROM " << this->dataTable;
    query << " WHERE sub_id IN (";
    
    for (unsigned int i = 0; i < numSubmissions; i++) {
        if (i != 0) query << ",";
        query << submissions[i].getId();
    }
    
    query << ")";
    
    sql::ResultSet *rs = stmt->executeQuery(query.str());
    Submission *current = NULL;
    
    while (rs->next()) {
        if (current == NULL || current->getId() != rs->getUInt(1)) {
            current = findById(submissions, numSubmissions, rs->getUInt(1));
        }
        
        current->setField(rs->getString(2), rs->getString(3));
    }
    
    delete rs;
}