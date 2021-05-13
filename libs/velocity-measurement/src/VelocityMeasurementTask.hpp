
#pragma once

#include <TaskSchedulerDeclarations.h>


class VelocityMeasurementTask : public Task
{
public:
  VelocityMeasurementTask(Scheduler* pScheduler, unsigned long interval);

  virtual bool Callback() override;
};
