
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
    m_DragIndicatorStore.add(entry);
}

int DataLogger::registerLogConfig(const LogConfig& config)
{
    return m_ConfigStore.registerConfig(config);
}

DataLogger::LogDataArray DataLogger::getLogDataArray() const
{
    LogDataArray data;

    for (size_t index=0; index < m_ConfigStore.size(); ++index)
    {
        data[index].m_Config = m_ConfigStore.get(index);
        data[index].m_Indicators = m_DragIndicatorStore.get(index);
    }

    return data;
}
