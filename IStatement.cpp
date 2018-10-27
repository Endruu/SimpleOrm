#include "IStatement.hpp"

void checkInput(IStatement& stmt, size_t idx)
{
	if (idx >= stmt.getNumberOfColumns()) throw std::out_of_range("Index " + std::to_string(idx) + " is out of range! Number of columns is only " + std::to_string(stmt.getNumberOfColumns()));
	if (stmt.columnIsNull(idx)) throw std::logic_error("Can not get value! Expected a non-null value while accessing index " + std::to_string(idx));
}

void IStatement::getValue(size_t idx, std::string& out)
{
	checkInput(*this, idx);

	_getValue(idx, out);
}

void IStatement::getValue(size_t idx, int64_t& out)
{
	checkInput(*this, idx);

	_getValue(idx, out);
}