
#pragma once

#include "LogStore.hpp"
#include "LogEntry.hpp"
#include "LogConfig.hpp"
#include "LogConfigStore.hpp"
#include "LogDragIndicatorStore.hpp"


class DataLogger
{
public:
    static DataLogger& getInstance();

    void addData(const LogEntry& entry);
    int registerLogConfig(const LogConfig& config);

private:
    LogStore<LogEntry, LOG_STORE_SIZE> m_Store;
    LogConfigStore<LOG_CONFIG_STORE_SIZE> m_ConfigStore;
    LogDragIndicatorStore<LOG_CONFIG_STORE_SIZE> m_DragIndicatorStore;
};
