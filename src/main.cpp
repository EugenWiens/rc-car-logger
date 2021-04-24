#include <Arduino.h>
#include <TaskScheduler.h>

#include "Logger.hpp"


class SchedulerContainer {
public:
  static Scheduler* getScheduler()
  {
    static Scheduler scheduler;

    return &scheduler;
  }
};

class Task1 : public Task
{
public:
  Task1()
  : Task(1000, TASK_FOREVER, SchedulerContainer::getScheduler(), true)
  {
    debugLog();
  }

  virtual bool Callback() override
  {
    debugLog() << "test";

    return true;
  }
};

class Task2 : public Task
{
public:
  Task2()
  : Task(2000, TASK_FOREVER, SchedulerContainer::getScheduler(), true)
  {
    debugLog();

  }

protected:
  virtual bool Callback() override
  {
    debugLog() << "test2";
    return true;
  }
};

Scheduler *pScheduler = SchedulerContainer::getScheduler();

Task1 t1;
Task2 t2;

void setup() {
  Serial.begin(115200);

  Serial.println("setup");
}

void loop() {
  pScheduler->execute();
}