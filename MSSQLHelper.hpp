#pragma once

#include <sqltypes.h>
#include <string>

class Connection
{
public:
    Connection(const char* file_name);
    ~Connection();

private:
    SQLHDBC hDbc = nullptr;

friend class Statement;

};

class Statement
{
public:
    Statement(const Connection& connection, const char* query);
    ~Statement();

    bool readNextRow();

    void getValue(int col, int32_t& val);
    void getValue(int col, int64_t& val);
    void getValue(int col, double& val);
    //void getValue(int col, std::string& val);
    void getValue(int col, std::string& val);
    //void getValue(int col, std::u16string& val);

private:
    SQLHSTMT hStmt = nullptr;
    bool done = false;

};