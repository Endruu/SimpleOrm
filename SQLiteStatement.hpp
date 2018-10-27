#pragma once

#include <IStatement.hpp>

#include <memory>

class SQLiteConnection;

struct sqlite3_stmt;
struct sqlite3;

class SQLiteStatement : public ISatement
{
public:
    SQLiteStatement(std::shared_ptr<sqlite3> connection, const char* query);
    ~SQLiteStatement() override;

    bool readNextRow() override;

    bool getValue(size_t idx, std::string& out) override;
	bool getValue(size_t idx, int64_t& out) override;

private:
    sqlite3_stmt * stmt = nullptr;
    std::shared_ptr<sqlite3> connection;
    bool done = false;

};