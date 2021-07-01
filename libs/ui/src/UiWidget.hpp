
#pragma once

#include <Adafruit_SSD1306.h>


class UiWidget
{
public:
    constexpr UiWidget(Adafruit_SSD1306* pHandler)
        : m_pHandler(pHandler)
    {}

    constexpr UiWidget()
        : m_pHandler(nullptr)
    {}

    virtual void setHandler(Adafruit_SSD1306* pHandler);
    virtual void show(int x, int y);
    virtual void draw(int x, int y) = 0;

protected:
    Adafruit_SSD1306* m_pHandler;

    int getPointForCentering(int length1, int length2) const;
};
