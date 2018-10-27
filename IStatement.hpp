#pragma once

#include <string>

class ISatement
{
public:
    virtual ~ISatement() {}

    virtual bool readNextRow() = 0;

	virtual bool getValue(size_t idx, std::string& out) = 0;
	virtual bool getValue(size_t idx, int64_t& out) = 0;
};

class StatementExtractor
{
public:
	StatementExtractor(ISatement& statement) : statement(statement) {}

	template<typename T>
	friend StatementExtractor& operator>>(StatementExtractor& extractor, T& value)
	{
		extractor.statement.getValue(extractor.idx++, value); // TODO error handling

		return extractor;
	}

private:
	ISatement& statement;
	size_t idx = 0;
};

template<typename T>
StatementExtractor operator>>(ISatement& statement, T& value)
{
	return StatementExtractor(statement) >> value;
}