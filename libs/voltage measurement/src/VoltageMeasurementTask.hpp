
#pragma once

#include <TaskSchedulerDeclarations.h>


class VoltageMeasurementTask : public Task
{
public:
  VoltageMeasurementTask(Scheduler* pScheduler, unsigned long interval);

  void setup();
  virtual bool Callback() override;

private:
  int m_LoggerId;
};
