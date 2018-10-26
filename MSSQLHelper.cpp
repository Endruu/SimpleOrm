#pragma once

#include "MSSQLHelper.hpp"

#include <sql.h>
#include <sqlext.h>

class Environment
{
    Environment()
    {
        SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
        SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    }

    ~Environment()
    {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    }

    SQLHENV hEnv = NULL;

public:

    static auto get()
    {
        static Environment env;
        return env.hEnv;
    }

};

Connection::Connection(const char *file_name)
{
    SQLAllocHandle(SQL_HANDLE_DBC, Environment::get(), &hDbc);

    SQLDriverConnect(hDbc,
                     NULL,
                     (SQLWCHAR *)file_name,
                     SQL_NTS,
                     NULL,
                     0,
                     NULL,
                     SQL_DRIVER_NOPROMPT);
}

Connection::~Connection()
{
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
}

Statement::Statement(const Connection &connection, const char *query)
{
    SQLAllocHandle(SQL_HANDLE_STMT, connection.hDbc, &hStmt);

    SQLExecDirect(hStmt, (SQLWCHAR *)query, SQL_NTS);

    SQLSMALLINT sNumResults = 0;
    SQLNumResultCols(hStmt, &sNumResults);

}

Statement::~Statement()
{
    SQLFreeStmt(hStmt, SQL_CLOSE);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}

bool Statement::readNextRow()
{
    const auto retcode = SQLFetch(hStmt);
    if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
    {
        done = false;
    }

    return !done;
}

void Statement::getValue(int col, short int &val) { SQLGetData(hStmt, col, SQL_C_SSHORT, &val, 0, NULL); }
void Statement::getValue(int col, int64_t &val) { SQLGetData(hStmt, col, SQL_C_DOUBLE, &val, 0, NULL); }
void Statement::getValue(int col, double &val) { SQLGetData(hStmt, col, SQL_C_DOUBLE, &val, 0, NULL); }
//void Statement::getValue(int col, std::string& val) { val = static_cast<const char*>(sqlite3_column_text(stmt, col)); }
void Statement::getValue(int col, std::string &val) { val = reinterpret_cast<const char *>(sqlite3_column_text(stmt, col)); }
//void Statement::getValue(int col, std::u16string& val) { val = sqlite3_column_text16(stmt, col); }