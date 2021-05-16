
#include "LogConfig.hpp"


LogConfig::LogConfig()
    : m_Valid(false)
{
}

LogConfig::LogConfig(const String& name, const String& unit)
    : m_Valid(true), m_Name(name), m_Unit(unit)
{
}

LogConfig::operator bool() const
{
    return m_Valid;
}

String LogConfig::getName() const
{
    return m_Name;
}

String LogConfig::getUnit() const
{
    return m_Unit;
}
