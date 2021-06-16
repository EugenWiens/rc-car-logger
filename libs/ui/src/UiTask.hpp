
#pragma once

#include "WorkerTask.hpp"


class UiTask : public WorkerTask
{
public:
  using WorkerTask::WorkerTask;

  void setup() override;

private:
  void run() override;

};
