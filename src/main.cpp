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

void setup() {
  Serial.begin(115200);
  debugLog() << "setup";
}

void loop() {
  scheduler.execute();
}