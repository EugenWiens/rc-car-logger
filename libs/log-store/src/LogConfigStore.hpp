
#pragma once
#include <stddef.h>
#include <array>
#include "LogConfig.hpp"


template <size_t N>
class LogConfigStore
{
public:
    int registerConfig(const LogConfig& config)
    {
        int slot = getFreeSlot();

        if (slot != -1)
        {
            m_ConfigArray[slot] = config;
        }

        return slot;
    }

    LogConfig get(int slotId) const
    {
        LogConfig config;

        if ((slotId >= 0) && (slotId < m_ConfigArray.size()))
        {
            config = m_ConfigArray[slotId];
        }

        return config;
    }

    unsigned int size() const
    {
        return N;
    }

private:
    std::array<LogConfig, N> m_ConfigArray;

    int getFreeSlot() const
    {
        int freeSlot = -1;
        for (int index = 0; index < m_ConfigArray.size(); ++index)
        {
            if (!m_ConfigArray[index])
            {
                freeSlot = index;
                break;
            }
        }

        return freeSlot;
    }
};

