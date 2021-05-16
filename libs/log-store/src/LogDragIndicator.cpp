
#include "LogDragIndicator.hpp"
#include <algorithm>
#include <float.h>


LogDragIndicator::LogDragIndicator()
    : m_Min(FLT_MAX), m_Max(0.0), m_Last(0.0)
{
}

void LogDragIndicator::set(const float value)
{
    m_Last = value;
    m_Min = std::min(m_Min, value);
    m_Max = std::max(m_Max, value);
}

float LogDragIndicator::getLast() const
{
    return m_Last;
}

float LogDragIndicator::getMin() const
{
    return m_Min;
}

float LogDragIndicator::getMax() const
{
    return m_Max;
}
