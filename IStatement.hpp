#pragma once

#include <string>

class IStatement
{
public:
    virtual ~IStatement() {}

    bool readNextRow();

	void getValue(size_t idx, std::string& out);
	void getValue(size_t idx, int64_t& out);

	virtual size_t numberOfReadColumns() = 0;
	virtual bool columnIsNull(size_t idx) = 0;

	size_t numberOfReadRows() const { return _idxOfActualRow;  }

private:
	virtual bool _readNextRow() = 0;
	virtual void _getValue(size_t idx, std::string& out) = 0;
	virtual void _getValue(size_t idx, int64_t& out) = 0;

	size_t _idxOfActualRow = 0;
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