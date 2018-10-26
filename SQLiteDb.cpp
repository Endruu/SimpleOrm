#include "SQLiteDb.hpp"

void SqliteDb::loadInto(DbRows<Example>& rows) const
{
    Statement stmt(conn, "SELECT ex_int, ex_text FROM ex_table");

    while( stmt.readNextRow() )
    {
        Example ex;
        stmt.getValue(0, ex.ExInt);
        stmt.getValue(1, ex.ExString);
        rows.rows.push_back(std::move(ex));
    }

}