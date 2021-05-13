
#pragma once

#include <TaskSchedulerDeclarations.h>


class VoltageMeasurementTask : public Task
{
public:
  VoltageMeasurementTask(Scheduler* pScheduler, unsigned long interval);

  virtual bool Callback() override;
};
