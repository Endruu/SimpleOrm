#include "SQLiteStatement.hpp"

#include <sqlite3.h>

SQLiteStatement::SQLiteStatement(std::shared_ptr<sqlite3> conn, const char *query_str) : connection(std::move(conn))
{
	if (sqlite3_prepare_v2(connection.get(), query_str, -1, &stmt, nullptr) != SQLITE_OK)
	{
		throw std::runtime_error(sqlite3_errmsg(connection.get()));
	}
}

SQLiteStatement::~SQLiteStatement()
{
	sqlite3_finalize(stmt);
}

bool SQLiteStatement::readNextRow()
{
	if (!done && sqlite3_step(stmt) != SQLITE_ROW)
	{
		done = true;
	}

	return !done;
}

size_t SQLiteStatement::getNumberOfColumns()
{
	return sqlite3_column_count(stmt);
}

bool SQLiteStatement::columnIsNull(size_t idx)
{
	return (sqlite3_column_type(stmt, idx) == SQLITE_NULL);
}

void SQLiteStatement::_getValue(size_t idx, std::string& out)
{
	auto str = reinterpret_cast<const char*>(sqlite3_column_text(stmt, idx));
	if (str)
	{
		out.assign(str);
	}
}

void SQLiteStatement::_getValue(size_t idx, int64_t& out)
{
	out = sqlite3_column_int64(stmt, idx);
}