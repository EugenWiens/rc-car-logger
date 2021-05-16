
#pragma once

#include <Arduino.h>


class LogConfig
{
public:
    LogConfig();
    LogConfig(const String& name, const String& unit);

    operator bool() const;

    String getName() const;
    String getUnit() const;

private:
    bool m_Valid;
    String m_Name;
    String m_Unit;
};
