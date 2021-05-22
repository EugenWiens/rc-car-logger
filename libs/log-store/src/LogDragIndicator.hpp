#pragma once

class LogDragIndicator
{
public:
    LogDragIndicator();

    void set(const float value);

    float getLast() const;
    float getMin() const;
    float getMax() const;

    operator bool() const;

private:
    float m_Min;
    float m_Max;
    float m_Last;
    bool m_Valid;
};