
#pragma once
#include <cstddef>
#include <Arduino.h>

enum class LogFormat
{
    noFormat,
    hex
};

class LogContext
{
public:
    constexpr LogContext(int line, const char* fileName)
        : m_Line(line), m_pFile(fileName)
    {}

    int getLineNumber() const { return m_Line; }
    const char* const getFileName() const { return m_pFile; }

private:
    const int m_Line;
    const char* m_pFile;
};

class LogWrapper
{
public:

    explicit LogWrapper(const LogContext& context);
    ~LogWrapper();

    LogWrapper(const LogWrapper&) = delete;
    LogWrapper(const LogWrapper&&) = delete;
    LogWrapper& operator =(const LogWrapper&) = delete;
    LogWrapper& operator =(const LogWrapper&&) = delete;

    LogWrapper& operator <<(const int number);
    LogWrapper& operator <<(const unsigned int number);
    LogWrapper& operator <<(const float number);

    LogWrapper& operator <<(const char* str);
    LogWrapper& operator <<(const String& str);

    LogWrapper& operator <<(const LogFormat format);

    template <typename T>
    LogWrapper& operator <<(const T& object)
    {
        *this << object.toString();

        return *this;
    }


private:
    constexpr static size_t m_BufferSize = 128;
    const LogContext& m_Context;
    char m_Buffer[m_BufferSize];
    size_t m_CurrentPosition;
    LogFormat m_Format;

    char* getBufferPosition();
    size_t getRemainingSize();
    void clearFormat();
};

#define debugLog() LogWrapper(LogContext(__LINE__, __FILE__))
