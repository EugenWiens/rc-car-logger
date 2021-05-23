#include <Arduino.h>
#include <TaskScheduler.h>

#include "DebugOut.hpp"
#include "WorkerTask.hpp"
#include "ModulesDefines.hpp"

Scheduler scheduler;

#if defined(VELOCITY_MEASUREMENT)
    #include "VelocityMeasurementTask.hpp"
    VelocityMeasurementTask velocityMeasurementTask(&scheduler, 1000);
#endif

#if defined(VOLTAGE_MEASUREMENT)
    #include "VoltageMeasurementTask.hpp"
    VoltageMeasurementTask voltageMeasurementTask(&scheduler, 1000);
#endif

#if defined(WEB_UI)
    #include "WebUiTask.hpp"
    WebUiTask webUiTask(&scheduler, 1000);
#endif

WorkerTask* workers[] =
{
#if defined(VELOCITY_MEASUREMENT)
    &velocityMeasurementTask,
#endif

#if defined(VOLTAGE_MEASUREMENT)
    &voltageMeasurementTask,
#endif

#if defined(WEB_UI)
    &webUiTask,
#endif
};

void
setup()
{
    Serial.begin(115200);
    debugLog() << "RC-Logger version:" << VERSION_TAG;

    for (WorkerTask* pWorker : workers)
    {
        if (pWorker)
        {
            pWorker->setup();
        }
    }
}

void loop()
{
    scheduler.execute();
}