
#pragma once

#include "WorkerTask.hpp"


class VoltageMeasurementTask : public WorkerTask
{
public:
    using WorkerTask::WorkerTask;

    void setup() override;

private:
    int m_LoggerIdForVoltage;
    int m_LoggerIdForCurrent;
    bool m_SuccessfullyInitialized;

    void run() override;
    void printIna226Config() const;
};
