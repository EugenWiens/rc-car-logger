
#pragma once

#include <string>


class LogEntry
{
public:
    LogEntry();
    LogEntry(const float& value);

    std::string toString();

private:
    unsigned int m_TimeStamp;
    float m_Value;
};

