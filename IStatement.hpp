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