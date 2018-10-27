#pragma once

#include <IStatement.hpp>

#include <memory>

class SQLiteConnection;

struct sqlite3_stmt;
struct sqlite3;

class SQLiteStatement : public IStatement
{
public:
    SQLiteStatement(std::shared_ptr<sqlite3> connection, const char* query);
    ~SQLiteStatement() override;

	size_t numberOfReadColumns() override;
	bool columnIsNull(size_t idx) override;

private:

    bool _readNextRow() override;
    void _getValue(size_t idx, std::string& out) override;
	void _getValue(size_t idx, int64_t& out) override;

    sqlite3_stmt * stmt = nullptr;
    std::shared_ptr<sqlite3> connection;
    bool done = false;

};