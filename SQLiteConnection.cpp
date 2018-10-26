#pragma once

#include "SQLiteConnection.hpp"
#include "SQLiteStatement.hpp"

#include <sqlite3.h>

SQLiteConnection::SQLiteConnection(const char *file_name)
{
    sqlite3 * conn = nullptr;
    sqlite3_open(file_name, &conn);

    connection = decltype(connection)(conn, [](auto p) {sqlite3_close(p); });
}

std::unique_ptr<ISatement> SQLiteConnection::query(const char * query_str)
{
    return std::make_unique<SQLiteStatement>(connection, query_str);
}
