
#include "VelocityMeasurementTask.hpp"
#include "DebugOut.hpp"


VelocityMeasurementTask::VelocityMeasurementTask(Scheduler* pScheduler)
    : Task(1000, TASK_FOREVER, pScheduler, true)
{
  debugLog();
}

bool VelocityMeasurementTask::Callback()
{
  debugLog() << "test";

  return true;
}
