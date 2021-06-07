
#pragma once

#include <Arduino.h>
#include "LogValue.hpp"


class LogEntry
{
public:
    LogEntry();
    LogEntry(int slotId, const LogValue& value);

    String toString() const;
    LogValue getValue() const;
    int getSlotId() const;
    unsigned int getTimeStamp() const;

private:
    int m_SlotId;
    unsigned int m_TimeStamp;
    LogValue m_Value;
};

