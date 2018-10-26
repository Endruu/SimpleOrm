#pragma once

#include "IDatabase.hpp"
#include "SQLiteHelper.hpp"

class SqliteDb : public IDatabase
{
public:
    SqliteDb(const char* file_name) : conn(file_name) {}

    Connection conn;

    void loadInto(DbRows<Example>& rows) const override;

};