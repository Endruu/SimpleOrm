#include "IStatement.hpp"

std::string location(IStatement& stmt, size_t idx)
{
	return "(Row:" + std::to_string(stmt.numberOfReadRows()) + " , Column:" + std::to_string(idx) + ")";
}

std::string locationAndName(IStatement& stmt, size_t idx)
{
	return "(Row:" + std::to_string(stmt.numberOfReadRows()) + " , ColumnIdx:" + std::to_string(idx) + ")";
}

void checkIdx(IStatement& stmt, size_t idx)
{
	if (idx >= stmt.numberOfReadColumns())
		throw std::out_of_range("Index is out of range! Number of columns is only " + std::to_string(stmt.numberOfReadColumns()) + "! " + location(stmt, idx));
}

void checkNull(IStatement& stmt, size_t idx)
{
	if (stmt.columnIsNull(idx))
		throw std::logic_error("Failed to get value! Expected a non-null value! " + locationAndName(stmt, idx));
}

bool IStatement::readNextRow()
{
	if (_readNextRow())
	{
		++_idxOfActualRow;
		return true;
	}
	return false;
}

void IStatement::getValue(size_t idx, std::string& out)
{
	checkNull(*this, idx);

	_getValue(idx, out);
}

void IStatement::getValue(size_t idx, int64_t& out)
{
	checkNull(*this, idx);

	_getValue(idx, out);
}

bool IStatement::columnIsNull(size_t idx)
{
	checkIdx(*this, idx);

	return _columnIsNull(idx);
}
