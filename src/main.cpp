#include <Arduino.h>
#include <TaskScheduler.h>

#include "DebugOut.hpp"
#include "WorkerTask.hpp"
#include "ModulesDefines.hpp"

Scheduler scheduler;

#if defined(GPS_DATA_MEASUREMENT)
    #include "GpsDataMeasurementTask.hpp"
    GpsDataMeasurementTask gpsDataMeasurementTask(&scheduler, 250);
#endif

#if defined(POWER_MEASUREMENT)
    #include "PowerMeasurementTask.hpp"
    PowerMeasurementTask powerMeasurementTask(&scheduler, 250);
#endif

#if defined(WEB_UI)
    #include "WebUiTask.hpp"
    WebUiTask webUiTask(&scheduler, 1000);
#endif

#if defined(UI)
    #include "UiTask.hpp"
    UiTask UiTask(&scheduler, 250);
#endif

WorkerTask* workers[] =
{
#if defined(GPS_DATA_MEASUREMENT)
    &gpsDataMeasurementTask,
#endif

#if defined(POWER_MEASUREMENT)
    &powerMeasurementTask,
#endif

#if defined(WEB_UI)
    &webUiTask,
#endif

#if defined(UI)
    &UiTask,
#endif
};

void setup()
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