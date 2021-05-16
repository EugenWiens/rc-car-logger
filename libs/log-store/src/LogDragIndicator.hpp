#pragma once

class LogDragIndicator
{
public:
    LogDragIndicator();

    void set(const float value);

    float getLast() const;
    float getMin() const;
    float getMax() const;

private:
    float m_Min;
    float m_Max;
    float m_Last;
};