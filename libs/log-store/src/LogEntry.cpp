
#include "LogEntry.hpp"
#include "TimeProvider.hpp"
#include "DebugOut.hpp"


LogEntry::LogEntry()
    : m_TimeStamp(0), m_Value()
{
}

LogEntry::LogEntry(const float& value)
    : m_TimeStamp(TimeProvider::getInstance().now()), m_Value()
{
    debugLog() << m_TimeStamp;
}
