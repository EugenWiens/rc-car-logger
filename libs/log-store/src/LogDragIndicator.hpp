#pragma once

#include "LogValue.hpp"

class LogDragIndicator
{
public:
    LogDragIndicator();

    void set(const LogValue& value);

    LogValue getLast() const;
    LogValue getMin() const;
    LogValue getMax() const;

    void clear();

private:
    LogValue m_Min;
    LogValue m_Max;
    LogValue m_Last;
};