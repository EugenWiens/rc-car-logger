
#pragma once

#include <Arduino.h>


class LogEntry
{
public:
    LogEntry();
    LogEntry(int slotId, const float& value);

    String toString() const;
    float getValue() const;
    int getSlotId() const;

private:
    int m_SlotId;
    unsigned int m_TimeStamp;
    float m_Value;
};

