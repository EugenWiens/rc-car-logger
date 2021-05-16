
#pragma once

#include <Arduino.h>


class TimeProvider
{
public:
    static TimeProvider& getInstance();

    unsigned int now() const;
    String nowAsString() const;

private:
    TimeProvider();
};
