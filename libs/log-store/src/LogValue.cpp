
#include "LogValue.hpp"


LogValue::LogValue()
    : m_Type(ValueType::invalid), m_FloatValue(0.0f), m_IntValue(0)
 {
 }


LogValue::LogValue(float value)
    : m_Type(ValueType::floatValue), m_FloatValue(value), m_IntValue(0)
{
}

LogValue::LogValue(int value)
    : m_Type(ValueType::intValue), m_FloatValue(0.0f), m_IntValue(value)
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

    if (m_Type == ValueType::intValue)
    {
        less = m_IntValue <= other.m_IntValue;
    }
    else if (m_Type == ValueType::floatValue)
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
        valueAsString = String(m_IntValue);
    }
    else if (m_Type == ValueType::floatValue)
    {
        valueAsString = String(m_FloatValue);
    }

    return valueAsString;
}
