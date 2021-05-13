
#include "VelocityMeasurementTask.hpp"
#include "DebugOut.hpp"


VelocityMeasurementTask::VelocityMeasurementTask(Scheduler* pScheduler, unsigned long interval)
    : Task(interval, TASK_FOREVER, pScheduler, true)
{
  debugLog();
}

bool VelocityMeasurementTask::Callback()
{
  debugLog() << "test";

  return true;
}
