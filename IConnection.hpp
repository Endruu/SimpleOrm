#pragma once

#include <IStatement.hpp>

#include <memory>
#include <string>

class IConnection
{
public:
    virtual std::unique_ptr<ISatement> query(const char * query_str) = 0;

    virtual ~IConnection() {}
};