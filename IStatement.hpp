#pragma once

#include <string>

class IStatement
{
public:
    virtual ~IStatement() {}

    virtual bool readNextRow() = 0;

	virtual bool getValue(size_t idx, std::string& out) = 0;
	virtual bool getValue(size_t idx, int64_t& out) = 0;
};

class StatementExtractor
{
public:
	StatementExtractor(IStatement& statement) : statement(statement) {}

	template<typename T>
	friend StatementExtractor& operator>>(StatementExtractor& extractor, T& value)
	{
		extractor.statement.getValue(extractor.idx++, value); // TODO error handling

		return extractor;
	}

private:
	IStatement& statement;
	size_t idx = 0;
};

template<typename T>
StatementExtractor operator>>(IStatement& statement, T& value)
{
	return StatementExtractor(statement) >> value;
}