
#pragma once

#include "LogStore.hpp"
#include "LogEntry.hpp"


class DataLogger
{
public:
    static DataLogger& getInstance();

    void addData(const LogEntry& entry);

private:
    LogStore<LogEntry, 8> m_Store;
};
