
#include "GpsDataMeasurementTask.hpp"
#include "DebugOut.hpp"
#include "LogConfig.hpp"
#include "DataLogger.hpp"

#include <Arduino.h>

GpsDataMeasurementTask::GpsDataMeasurementTask(Scheduler *pScheduler, unsigned long interval)
    : WorkerTask(pScheduler, interval), m_LoggerIdForSpeed(-1), m_LoggerIdForSatellites(-1)
{
    Serial2.begin(9600);
}

void GpsDataMeasurementTask::setup()
{
    LogConfig configSpeed("Speed", "km/h", IconProvider::IconType::speed);
    m_LoggerIdForSpeed = DataLogger::getInstance().registerLogConfig(configSpeed);
    debugLog() << "Speed registered config for id" << m_LoggerIdForSpeed;

    LogConfig configSatellite("Satellites", "", IconProvider::IconType::satellite);
    m_LoggerIdForSatellites = DataLogger::getInstance().registerLogConfig(configSatellite);
    debugLog() << "Satellites registered config for id" << m_LoggerIdForSatellites;
}

void GpsDataMeasurementTask::run()
{
    while (Serial2.available() > 0)
    {
        char byte = Serial2.read();
        if (m_Gps.encode(byte))
        {
            handleData();
        }
    }

    if (millis() > 5000 && m_Gps.charsProcessed() < 10)
    {
        static bool error = false;

        if (error == false)
        {
            error = true;
            debugLog() << "No GPS detected: check wiring.";
        }
    }
}

void GpsDataMeasurementTask::handleData()
{
    if (m_Gps.speed.isValid())
    {
        if (m_Gps.speed.isUpdated())
        {
            LogValue value(static_cast<float>(m_Gps.speed.kmph()));
            DataLogger::getInstance().addData(LogEntry(m_LoggerIdForSpeed, value));
        }
    }

    if (m_Gps.satellites.isValid())
    {
        if (m_Gps.satellites.isUpdated())
        {
            LogValue value(static_cast<int>(m_Gps.satellites.value()));
            DataLogger::getInstance().addData(LogEntry(m_LoggerIdForSatellites, value));
        }
    }
}

void GpsDataMeasurementTask::printData()
{
    Serial.print(F("Satellites: "));
    if (m_Gps.satellites.isValid())
    {
        Serial.print(m_Gps.satellites.value());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.print(F(" Location: "));
    if (m_Gps.location.isValid())
    {
        Serial.print(m_Gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(m_Gps.location.lng(), 6);
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.print(F("  Date/Time: "));
    if (m_Gps.date.isValid())
    {
        Serial.print(m_Gps.date.month());
        Serial.print(F("/"));
        Serial.print(m_Gps.date.day());
        Serial.print(F("/"));
        Serial.print(m_Gps.date.year());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.print(F(" "));
    if (m_Gps.time.isValid())
    {
        if (m_Gps.time.hour() < 10)
            Serial.print(F("0"));
        Serial.print(m_Gps.time.hour());
        Serial.print(F(":"));
        if (m_Gps.time.minute() < 10)
            Serial.print(F("0"));
        Serial.print(m_Gps.time.minute());
        Serial.print(F(":"));
        if (m_Gps.time.second() < 10)
            Serial.print(F("0"));
        Serial.print(m_Gps.time.second());
        Serial.print(F("."));
        if (m_Gps.time.centisecond() < 10)
            Serial.print(F("0"));
        Serial.print(m_Gps.time.centisecond());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.print(F(" Speed: "));
    if (m_Gps.speed.isValid())
    {
        Serial.print(m_Gps.speed.kmph());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.println();
}
