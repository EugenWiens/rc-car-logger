
#pragma once

#include <TaskSchedulerDeclarations.h>


class VelocityMeasurementTask : public Task
{
public:
  VelocityMeasurementTask(Scheduler* pScheduler);

  virtual bool Callback() override;
};
