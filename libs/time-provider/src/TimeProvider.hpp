
#pragma once


class TimeProvider
{
public:
    static TimeProvider& getInstance();

    unsigned int now();

private:
    TimeProvider();
};
