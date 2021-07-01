
#pragma once

#include <Arduino.h>
#include "IconProvider.hpp"


class LogConfig
{
public:
    LogConfig();
    LogConfig(const String& name, const String& unit, IconProvider::IconType iconType);

    operator bool() const;

    String getName() const;
    String getUnit() const;
    IconProvider::IconType getIcon() const;

private:
    bool m_Valid;
    String m_Name;
    String m_Unit;
    IconProvider::IconType m_IconType;
};
