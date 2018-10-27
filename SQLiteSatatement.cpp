#include "SQLiteStatement.hpp"

#include <sqlite3.h>

SQLiteStatement::SQLiteStatement(std::shared_ptr<sqlite3> conn, const char *query_str) : connection(std::move(conn))
{
    sqlite3_prepare_v2(connection.get(), query_str, -1, &stmt, nullptr);
}

SQLiteStatement::~SQLiteStatement()
{
    sqlite3_finalize(stmt);
}

bool SQLiteStatement::readNextRow()
{
    if (!done && sqlite3_step(stmt) != SQLITE_ROW)
    {
        done = false;
    }

    return !done;
}