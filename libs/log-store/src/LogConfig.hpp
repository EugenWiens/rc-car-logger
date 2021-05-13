
#pragma once

#include <Arduino.h>


class LogConfig
{
public:
    LogConfig();
    LogConfig(const String& name, const String& unit);

    bool operator!() const;


private:
    bool m_Valid;
    String m_Name;
    String m_Unit;
};
