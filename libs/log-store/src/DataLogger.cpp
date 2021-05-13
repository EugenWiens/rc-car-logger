
#include "DataLogger.hpp"
#include "DebugOut.hpp"


DataLogger& DataLogger::getInstance()
{
    static DataLogger dataLogger;

    return dataLogger;
}

void DataLogger::addData(const LogEntry& entry)
{
    debugLog() << entry;
    m_Store.push(entry);
    m_DragIndicatorStore.add(entry);
}

int DataLogger::registerLogConfig(const LogConfig& config)
{
    return m_ConfigStore.registerConfig(config);
}
