
#include "DebugOut.hpp"

#include <Arduino.h>
#include <string.h>


LogWrapper::LogWrapper(const LogContext& context)
    : m_Context(context), m_CurrentPosition(0)
{
}

LogWrapper::~LogWrapper()
{
    char time[16] = {};
    snprintf(time, sizeof(time), "[%012lu] ", millis());
    Serial.print(time);
    Serial.print(m_Context.getFileName());
    Serial.print(":");
    Serial.print(m_Context.getLineNumber());
    Serial.print(" > ");
    Serial.println(m_Buffer);
}

LogWrapper& LogWrapper::operator <<(const int number)
{
    int processed = 0;

    if (m_Format == LogFormat::hex)
    {
        processed = snprintf(getBufferPosition(), getRemainingSize(), "%#x ", number);
    }
    else
    {
        processed = snprintf(getBufferPosition(), getRemainingSize(), "%d ", number);
    }

    m_CurrentPosition += processed;

    clearFormat();
    return *this;
}


LogWrapper& LogWrapper::operator <<(const unsigned int number)
{
    int processed = 0;

    if (m_Format == LogFormat::hex)
    {
        processed = snprintf(getBufferPosition(), getRemainingSize(), "%#x ", number);
    }
    else
    {
        processed = snprintf(getBufferPosition(), getRemainingSize(), "%u ", number);
    }

    m_CurrentPosition += processed;

    clearFormat();
    return *this;
}

LogWrapper& LogWrapper::operator <<(const float number)
{
    int processed = snprintf(getBufferPosition(), getRemainingSize(), "%f ", number);
    m_CurrentPosition += processed;

    return *this;
}

LogWrapper& LogWrapper::operator <<(const char* str)
{
    int processed = snprintf(getBufferPosition(), getRemainingSize(), "%s ", str);
    m_CurrentPosition += processed;

    clearFormat();
    return *this;
}

LogWrapper& LogWrapper::operator <<(const String& str)
{
    *this << str.c_str();

    return *this;
}

LogWrapper& LogWrapper::operator <<(const LogFormat format)
{
    m_Format = format;

    return *this;
}

char *LogWrapper::getBufferPosition()
{
  size_t position = m_CurrentPosition;

  if (position > m_BufferSize)
  {
    position = m_BufferSize;
  }

  return &m_Buffer[position];
}

size_t LogWrapper::getRemainingSize()
{
  size_t remainingSize = 0;

  if (m_BufferSize > m_CurrentPosition)
  {
    remainingSize = m_BufferSize - m_CurrentPosition;
  }

  return remainingSize;
}

void LogWrapper::clearFormat()
{
    m_Format = LogFormat::noFormat;
}
