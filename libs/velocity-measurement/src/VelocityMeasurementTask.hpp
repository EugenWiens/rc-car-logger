
#pragma once

#include "WorkerTask.hpp"
#include <TinyGPS++.h>


class VelocityMeasurementTask : public WorkerTask
{
public:
    VelocityMeasurementTask(Scheduler *pScheduler, unsigned long interval);

    void setup() override;

private:
    int m_LoggerIdForSpeed;
    int m_LoggerIdForSatellites;
    TinyGPSPlus m_Gps;

    void run() override;

    void handleData();
    void printData();
};
