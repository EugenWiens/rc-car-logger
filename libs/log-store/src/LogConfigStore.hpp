
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

    LogConfig getConfig(int slot)
    {
        LogConfig config;

        if ((slot >= 0) && (slot < m_ConfigArray.size()))
        {
            config = m_ConfigArray[slot];
        }

        return config;
    }

private:
    std::array<LogConfig, N> m_ConfigArray;

    int getFreeSlot()
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

