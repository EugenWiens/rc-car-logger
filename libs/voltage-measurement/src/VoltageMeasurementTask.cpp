
#include "VoltageMeasurementTask.hpp"
#include "DebugOut.hpp"
#include "DataLogger.hpp"
#include "LogEntry.hpp"
#include <cstdlib>


void VoltageMeasurementTask::setup()
{
    LogConfig config("Battery", "V");
    m_LoggerId = DataLogger::getInstance().registerLogConfig(config);
    debugLog() << "registered config for id" << m_LoggerId;
}

void VoltageMeasurementTask::run()
{
    LogValue value(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 60.0f);
    DataLogger::getInstance().addData(LogEntry(m_LoggerId, value));
}
