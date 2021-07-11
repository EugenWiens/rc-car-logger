
#include "PowerMeasurementTask.hpp"
#include "DebugOut.hpp"
#include "DataLogger.hpp"
#include "LogEntry.hpp"
#include <cstdlib>
#include <Wire.h>
#include <INA226.h>
#include "IconProvider.hpp"


INA226 ina(Wire);

void PowerMeasurementTask::setup()
{
    LogConfig configVoltage("Voltage", "V", IconProvider::IconType::batterie);
    m_LoggerIdForVoltage = DataLogger::getInstance().registerLogConfig(configVoltage);
    LogConfig configCurrent("Current", "A", IconProvider::IconType::batterie);
    m_LoggerIdForCurrent = DataLogger::getInstance().registerLogConfig(configCurrent);

    debugLog() << "registered config for ids voltage:" << m_LoggerIdForVoltage << "current:" << m_LoggerIdForCurrent;

    debugLog() << ("Initialize INA226");
    Wire.begin();

    m_SuccessfullyInitialized = ina.begin(0x45); // i2c address is 0x45

    if (m_SuccessfullyInitialized)
    {
        ina.configure(INA226_AVERAGES_1, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);

        // Calibrate INA226. Rshunt = 0.0005 ohm, Max excepted current = 130A
        ina.calibrate(0.0005, 130);
    }

    printIna226Config();
}

void PowerMeasurementTask::run()
{
    LogValue voltageValue(static_cast<float>(ina.readBusVoltage()));
    DataLogger::getInstance().addData(LogEntry(m_LoggerIdForVoltage, voltageValue));

    LogValue currentValue(static_cast<float>(ina.readShuntCurrent()));
    DataLogger::getInstance().addData(LogEntry(m_LoggerIdForCurrent, currentValue));
}

void PowerMeasurementTask::printIna226Config() const
{
    debugLog() << "Mode:" << static_cast<int>(ina.getMode());
    debugLog() << "Samples average:" << static_cast<int>(ina.getAverages());
    debugLog() << "Bus conversion time:" << static_cast<int>(ina.getBusConversionTime());
    debugLog() << "Shunt conversion time:" << static_cast<int>(ina.getShuntConversionTime());
    debugLog() << "Max possible current:" << ina.getMaxPossibleCurrent() << "A";
    debugLog() << "Max current:" << ina.getMaxCurrent() << "A";
    debugLog() << "Max shunt voltage:" << ina.getMaxShuntVoltage() << "V";
    debugLog() << "Max power:" << ina.getMaxPower() << "W";
}

