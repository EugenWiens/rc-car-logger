
#pragma once

#include "Arduino.h"


class LogValue
{
public:
    explicit LogValue();
    explicit LogValue(float value);
    explicit LogValue(int value);

    LogValue min(const LogValue& other) const;
    LogValue max(const LogValue& other) const;
    bool operator<(const LogValue& other) const;
    bool operator>(const LogValue& other) const;

    String toString() const;

private:
    enum class ValueType {
        invalid,
        floatValue,
        intValue
    };

    ValueType m_Type;
    float m_FloatValue;
};
