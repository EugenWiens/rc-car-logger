
#pragma once

#include "WorkerTask.hpp"


class VoltageMeasurementTask : public WorkerTask
{
public:
    using WorkerTask::WorkerTask;

    void setup() override;

private:
    int m_LoggerId;

    void run() override;
};
