
#include "VoltageMeasurementTask.hpp"
#include "DebugOut.hpp"
#include "DataLogger.hpp"
#include "LogEntry.hpp"
#include <cstdlib>


VoltageMeasurementTask::VoltageMeasurementTask(Scheduler* pScheduler, unsigned long interval)
    : Task(interval, TASK_FOREVER, pScheduler, true), m_LoggerId(-1)
{
  debugLog();
}

void VoltageMeasurementTask::setup()
{
  LogConfig config("Battery", "V");
  m_LoggerId = DataLogger::getInstance().registerLogConfig(config);
}

bool VoltageMeasurementTask::Callback()
{
  debugLog() << "test";
  float value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

  DataLogger::getInstance().addData(LogEntry(m_LoggerId, value));

  return true;
}


