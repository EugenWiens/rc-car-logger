#pragma once

#include <stddef.h>
#include <array>
#include <LogEntry.hpp>
#include <algorithm>


template <size_t N>
class LogDragIndicatorStore
{
public:
    struct Indicators{
        float m_Min;
        float m_Max;
        float m_Last;

        Indicators()
            : m_Min(0.0), m_Max(0.0), m_Last(0.0) {}
    };

    void add(const LogEntry& entry)
    {
        int slotId = entry.getSlotId();

        if ((slotId > 0) && (slotId < m_Indicators.size()))
        {
            float value = entry.getValue();
            m_Indicators[slotId].m_Last = value;
            m_Indicators[slotId].m_Min = std::min(m_Indicators[slotId].m_Min, value);
            m_Indicators[slotId].m_Max = std::max(m_Indicators[slotId].m_Max, value);
        }
    }

private:
    std::array<Indicators, N> m_Indicators;
};
