#pragma once

#include <IConnection.hpp>

struct sqlite3;

class SQLiteConnection : public IConnection
{
public:
    SQLiteConnection(const char* file_name);

    std::unique_ptr<ISatement> query(const char * query_str) override;

private:
    std::shared_ptr<sqlite3> connection;

};
