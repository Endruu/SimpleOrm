#include "SQLiteDb.hpp"

int main()
{
    const auto db = SqliteDb("db_path") ;
    const auto rows = loadRows<Example>(db);
}