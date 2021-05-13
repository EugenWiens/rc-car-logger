
#pragma once

#include <stddef.h>
#include "DebugOut.hpp"

template <typename T, size_t N>
class LogStore
{
public:
    constexpr LogStore()
        : m_Head(0), m_Tail(N-1)
    {
        static_assert((N > 1) && !(N & (N - 1)), "The size of the LogStore must be a power of two.");
    }

    void push(const T& entry)
    {
        increaseHead();
        m_Buffer[m_Head] = entry;
    }

    T pull()
    {
        increase(m_Tail);
        return m_Buffer[m_Tail];
    }

    size_t getFillSize()
    {
        debugLog() << "size:" << N << "tail:" << m_Tail << "head:" << m_Head;
        size_t fillSize = 0;

        if (m_Head == m_Tail)
        {
            fillSize = 0;
        }
        else if(m_Head > m_Tail)
        {
            fillSize = m_Head - m_Tail;
        }
        else if( m_Tail > m_Head)
        {
            fillSize = N - m_Tail + m_Head;
        }

        return fillSize;
    }

private:
    T m_Buffer[N];
    size_t m_Head;
    size_t m_Tail;

    void increaseHead()
    {
        increase(m_Head);

        if (m_Head == m_Tail)
        {
            increase(m_Tail);
        }
    }

    void increaseTail()
    {
        if (getFillSize() > 0)
        {
            increase(m_Tail);
        }

    }

    void increase(size_t& position)
    {
        position++;
        position &= (N-1);
    }
};
