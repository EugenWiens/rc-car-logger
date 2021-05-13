#include <Arduino.h>
#include <TaskScheduler.h>

#include "DebugOut.hpp"
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

void setup() {
  Serial.begin(115200);
  debugLog() << "setup";


#if defined(WEB_UI)
  webUiTask.setup();
#endif
}

void loop() {
  scheduler.execute();
}