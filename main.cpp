#include "SQLiteConnection.hpp"

#include "Example.hpp"

#include <vector>
#include <iostream>

IConnection& operator>>(IConnection& conn, std::vector<Example>& exs)
{
    auto stmt = conn.query("SELECT ex_int, ex_text FROM ex_table");

    while (stmt->readNextRow())
    {
        Example ex;

        stmt->getValue(0, ex.ExInt);
        stmt->getValue(1, ex.ExString);

        exs.push_back(std::move(ex));
    }

    return conn;
}

int main()
{
    // const auto db = SqliteDb("db_path") ;
    // const auto rows = loadRows<Example>(db);

    std::cout << "BEGIN!" << std::endl;

    try
    {

    std::unique_ptr<IConnection> conn = std::make_unique<SQLiteConnection>(R"(E:\MyPlayground\Cpp\SimpleOrm\test_db.db)");

    std::vector<Example> rows;

    *conn >> rows;

    for(const auto& ex : rows)
    {
        std::cout << "Example: " << ex.ExInt  << ' ' << ex.ExString << '\n';
    }

    }
    catch(const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "TADA!" << std::endl;
}