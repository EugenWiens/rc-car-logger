
#include "VoltageMeasurementTask.hpp"
#include "DebugOut.hpp"


VoltageMeasurementTask::VoltageMeasurementTask(Scheduler* pScheduler)
    : Task(1000, TASK_FOREVER, pScheduler, true)
{
  debugLog();
}

bool VoltageMeasurementTask::Callback()
{
  debugLog() << "test";

  return true;
}
