#pragma once

class ISatement
{
public:
    virtual ~ISatement() {}

    virtual bool readNextRow() = 0;
};