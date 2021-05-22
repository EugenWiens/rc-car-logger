
#pragma once

#include "LogStore.hpp"
#include "LogEntry.hpp"
#include "LogConfig.hpp"
#include "LogConfigStore.hpp"
#include "LogDragIndicatorStore.hpp"
#include "LogDragIndicator.hpp"


class DataLogger
{
public:
    struct LogData
    {
        LogConfig m_Config;
        LogDragIndicator m_Indicators;
    };

    using LogDataArray = std::array<LogData, LOG_CONFIG_STORE_SIZE>;

    static DataLogger& getInstance();

    void addData(const LogEntry& entry);
    int registerLogConfig(const LogConfig& config);
    LogDataArray getLogDataArray() const;
    void clearAllDragIndicators();

private:
    LogStore<LogEntry, LOG_STORE_SIZE> m_Store;
    LogConfigStore<LOG_CONFIG_STORE_SIZE> m_ConfigStore;
    LogDragIndicatorStore<LOG_CONFIG_STORE_SIZE> m_DragIndicatorStore;
};
