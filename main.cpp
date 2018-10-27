#include "SQLiteConnection.hpp"

#include "Example.hpp"

#include <queue>
#include <iostream>

int main()
{
    // const auto db = SqliteDb("db_path") ;
    // const auto rows = loadRows<Example>(db);

    std::cout << "BEGIN!" << std::endl;

    try
    {

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
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "TADA!" << std::endl;
}