#pragma once

#include "Example.hpp"

#include <vector>

class IDatabase;

template<typename DbRow>
class DbRows
{
public:
    std::vector<DbRow> rows;
    void loadFrom(const IDatabase& db);// override;

    //size, iterators
    //DbRows<DbRow> selectAll(pred)
    //DbRow selectFirst(pred)
    //size_t count(pred)

};

class IDatabase
{
public:
    virtual ~IDatabase() {}

    virtual void loadInto(DbRows<Example>& rows) const = 0;

};

template<typename DbRow>
void DbRows<DbRow>::loadFrom(const IDatabase& db) { db.loadInto(*this); }

template<typename T>
DbRows<T> loadRows(const IDatabase& db)
{
    DbRows<T> rows;
    rows.loadFrom(db);
    return rows;
}