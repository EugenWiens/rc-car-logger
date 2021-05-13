
#include "LogConfig.hpp"


LogConfig::LogConfig()
    : m_Valid(false)
{
}

LogConfig::LogConfig(const String& name, const String& unit)
    : m_Valid(true), m_Name(name), m_Unit(unit)
{
}

bool LogConfig::operator!() const
{
    return !m_Valid;
}