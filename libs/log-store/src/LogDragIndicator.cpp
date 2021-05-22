
#include "LogDragIndicator.hpp"
#include "DebugOut.hpp"


LogDragIndicator::LogDragIndicator()
{
}

void LogDragIndicator::set(const LogValue& value)
{
    m_Last = value;
    m_Min = m_Min.min(value);
    m_Max = m_Max.max(value);
}

LogValue LogDragIndicator::getLast() const
{
    return m_Last;
}

LogValue LogDragIndicator::getMin() const
{
    return m_Min;
}

LogValue LogDragIndicator::getMax() const
{
    return m_Max;
}

void LogDragIndicator::clear()
{
    m_Min = LogValue();
    m_Max = LogValue();
    m_Last = LogValue();
}
