#pragma once

#include "SQLiteHelper.hpp"

#include <sqlite3.h>

Connection::Connection(const char *file_name)
{
    sqlite3_open(file_name, &conn);
}

Connection::~Connection()
{
    sqlite3_close(conn);
}

Statement::Statement(const Connection &connection, const char *query)
{
    sqlite3_prepare_v2(connection.conn, query, -1, &stmt, nullptr);
}

Statement::~Statement()
{
    sqlite3_finalize(stmt);
}

bool Statement::readNextRow()
{
    if (!done && sqlite3_step(stmt) != SQLITE_ROW)
    {
        done = false;
    }

    return !done;
}

void Statement::getValue(int col, int32_t &val) { val = sqlite3_column_int(stmt, col); }
void Statement::getValue(int col, int64_t &val) { val = sqlite3_column_int64(stmt, col); }
void Statement::getValue(int col, double &val) { val = sqlite3_column_double(stmt, col); }
//void Statement::getValue(int col, std::string& val) { val = static_cast<const char*>(sqlite3_column_text(stmt, col)); }
void Statement::getValue(int col, std::string &val) { val = reinterpret_cast<const char *>(sqlite3_column_text(stmt, col)); }
//void Statement::getValue(int col, std::u16string& val) { val = sqlite3_column_text16(stmt, col); }