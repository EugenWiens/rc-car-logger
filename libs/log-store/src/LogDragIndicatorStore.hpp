#pragma once

#include <stddef.h>
#include <array>
#include <LogEntry.hpp>
#include "LogDragIndicator.hpp"
#include <algorithm>


template <size_t N>
class LogDragIndicatorStore
{
public:
    void add(const LogEntry& entry)
    {
        int slotId = entry.getSlotId();

        if ((slotId >= 0) && (slotId < m_Indicators.size()))
        {
            m_Indicators[slotId].set(entry.getValue());
        }
    }

    LogDragIndicator get(int slotId) const
    {
        LogDragIndicator values;

        if ((slotId >= 0) && (slotId < m_Indicators.size()))
        {
            values = m_Indicators[slotId];
        }

        return values;
    }

private:
    std::array<LogDragIndicator, N> m_Indicators;
};
