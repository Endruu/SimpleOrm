#pragma once

#include <IStatement.hpp>

#include <memory>

struct SQLiteConnection;

struct sqlite3_stmt;
struct sqlite3;

class SQLiteStatement : public ISatement
{
public:
    SQLiteStatement(std::shared_ptr<sqlite3> connection, const char* query);
    ~SQLiteStatement() override;

    bool readNextRow() override;

private:
    sqlite3_stmt * stmt = nullptr;
    std::shared_ptr<sqlite3> connection;
    bool done = false;

};