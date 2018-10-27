#include "SQLiteConnection.hpp"
#include "SQLiteStatement.hpp"

#include <sqlite3.h>

SQLiteConnection::SQLiteConnection(const char *file_name)
{
    sqlite3 * conn = nullptr;
    const auto ec = sqlite3_open(file_name, &conn);
    connection = decltype(connection)(conn, [](auto p)
    {
        if(p != nullptr)
        {
            sqlite3_close(p);
        }
    });

    if( ec != SQLITE_OK )
    {
        throw std::runtime_error(sqlite3_errmsg(conn));
    }

}

std::unique_ptr<IStatement> SQLiteConnection::query(const char * query_str)
{
    return std::make_unique<SQLiteStatement>(connection, query_str);
}
