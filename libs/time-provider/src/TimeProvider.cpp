
#include "TimeProvider.hpp"

#include <chrono>


TimeProvider::TimeProvider()
{
}


TimeProvider& TimeProvider::getInstance()
{
    static TimeProvider timeProvider;

    return timeProvider;
}

unsigned int TimeProvider::now() const
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return millis;
}

String TimeProvider::nowAsString() const
{
    unsigned int timeStamp = now();

    return String(timeStamp);
}
