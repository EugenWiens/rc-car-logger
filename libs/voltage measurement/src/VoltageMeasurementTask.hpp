
#pragma once

#include <TaskSchedulerDeclarations.h>


class VoltageMeasurementTask : public Task
{
public:
  VoltageMeasurementTask(Scheduler* pScheduler);

  virtual bool Callback() override;
};
