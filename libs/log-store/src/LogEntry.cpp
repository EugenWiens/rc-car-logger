
#include "LogEntry.hpp"
#include "TimeProvider.hpp"
#include "DebugOut.hpp"


LogEntry::LogEntry()
    : m_SlotId(-1), m_TimeStamp(0), m_Value()
{
}

LogEntry::LogEntry(int slotId, const float& value)
    : m_SlotId(slotId), m_TimeStamp(TimeProvider::getInstance().now()), m_Value(value)
{
}

String LogEntry::toString() const
{
    return String("{ slotId: ") + m_SlotId + String(" time: ") + m_TimeStamp + String(" value: ") + m_Value + String(" }");
}

float LogEntry::getValue() const
{
    return m_Value;
}

int LogEntry::getSlotId() const
{
    return m_SlotId;
}
