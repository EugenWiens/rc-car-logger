
#include "DataLogger.hpp"
#include "DebugOut.hpp"


DataLogger& DataLogger::getInstance()
{
    static DataLogger dataLogger;

    return dataLogger;
}

void DataLogger::addData(const LogEntry& entry)
{
    m_Store.push(entry);
}
