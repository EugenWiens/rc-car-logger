
#include "LogConfig.hpp"


LogConfig::LogConfig()
    : m_Valid(false)
{
}

LogConfig::LogConfig(const String& name, const String& unit, IconProvider::IconType iconType)
    : m_Valid(true), m_Name(name), m_Unit(unit), m_IconType(iconType)
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

IconProvider::IconType LogConfig::getIcon() const
{
    return m_IconType;
}

