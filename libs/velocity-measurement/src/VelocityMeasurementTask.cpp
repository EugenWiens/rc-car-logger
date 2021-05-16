
#include "VelocityMeasurementTask.hpp"
#include "DebugOut.hpp"
#include "LogConfig.hpp"
#include "DataLogger.hpp"


void VelocityMeasurementTask::setup()
{
    LogConfig config("Speed", "km/h");
    m_LoggerId = DataLogger::getInstance().registerLogConfig(config);
    debugLog() << "registered config for id" << m_LoggerId;}

void VelocityMeasurementTask::run()
{
    float value = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 10.0;
    DataLogger::getInstance().addData(LogEntry(m_LoggerId, value));
}
