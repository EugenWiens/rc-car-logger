
#include "LogValue.hpp"


LogValue::LogValue()
    : m_Type(ValueType::invalid), m_FloatValue(0.0f)
 {
 }

LogValue::LogValue(float value)
    : m_Type(ValueType::floatValue), m_FloatValue(value)
{
}

LogValue::LogValue(int value)
    : m_Type(ValueType::intValue), m_FloatValue(static_cast<float>(value))
{
}

LogValue LogValue::min(const LogValue& other) const
{
    if (m_Type == ValueType::invalid)
    {
        return other;
    }
    else
    {
        return std::min(*this, other);
    }
}

LogValue LogValue::max(const LogValue& other) const
{
    if (m_Type == ValueType::invalid)
    {
        return other;
    }
    else
    {
        return std::max(*this, other);
    }
}

bool LogValue::operator<(const LogValue& other) const
{
    bool less = false;

    if (m_Type != ValueType::invalid)
    {
        less = m_FloatValue <= other.m_FloatValue;
    }

    return less;
}

String LogValue::toString() const
{
    String valueAsString("---");

    if (m_Type == ValueType::intValue)
    {
        valueAsString = String(static_cast<int>(m_FloatValue));
    }
    else if (m_Type == ValueType::floatValue)
    {
        valueAsString = String(m_FloatValue);
    }

    return valueAsString;
}
