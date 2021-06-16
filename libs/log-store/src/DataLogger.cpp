
#include "DataLogger.hpp"
#include "DebugOut.hpp"

DataLogger &DataLogger::getInstance()
{
    static DataLogger dataLogger;

    return dataLogger;
}

void DataLogger::addData(const LogEntry &entry)
{
    m_Store.push(entry);
    m_DragIndicatorStore.add(entry);
}

int DataLogger::registerLogConfig(const LogConfig &config)
{
    return m_ConfigStore.registerConfig(config);
}

DataLogger::LogDataArray DataLogger::getLogDataArray() const
{
    LogDataArray data;

    for (size_t index = 0; index < m_ConfigStore.size(); ++index)
    {
        data[index].m_Config = m_ConfigStore.get(index);
        data[index].m_Indicators = m_DragIndicatorStore.get(index);
    }

    return data;
}

void DataLogger::clearAllDragIndicators()
{
    m_DragIndicatorStore.clearAll();
}

void DataLogger::getExportDataHeader(String &headerData) const
{
    headerData += "Timestamp, ";

    for (size_t index = 0; index < m_ConfigStore.size(); ++index)
    {
        LogConfig config = m_ConfigStore.get(index);
        headerData += config.getName() + "[" + config.getUnit() + "],";
    }
}

void DataLogger::getExportData(String &data)
{
    while (m_Store.getFillSize() > 0)
    {
        const auto &oneEntry = m_Store.pull();
        size_t index = 0;

        data += oneEntry.getTimeStamp();

        for (; index < m_ConfigStore.size(); ++index)
        {
            data += ",";

            if (index == oneEntry.getSlotId())
            {
                data += oneEntry.getValue().toString();
            }
        }

        data += '\n';
    }
}

bool DataLogger::exportDataAvailable() const
{
    return m_Store.getFillSize() > 0;
}

const LogConfig DataLogger::getLogConfig(int index) const
{
    return m_ConfigStore.get(index);
}

const LogDragIndicator DataLogger::getLogDragIndicator(int index) const
{
    return m_DragIndicatorStore.get(index);
}
