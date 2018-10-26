#include "SQLiteConnection.hpp"

#include "Example.hpp"

#include <queue>

int main()
{
    // const auto db = SqliteDb("db_path") ;
    // const auto rows = loadRows<Example>(db);

    std::unique_ptr<IConnection> conn = std::make_unique<SQLiteConnection>("...");

    std::queue<Example> rows;

    auto stmt = conn->query("SELECT ex_int, ex_text FROM ex_table");

    while (stmt->readNextRow())
    {
        Example ex;

        //stmt.getValue(0, ex.ExInt);
        //stmt.getValue(1, ex.ExString);

        rows.push(std::move(ex));
    }
}