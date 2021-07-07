
#include "Icon.hpp"
#include "DebugOut.hpp"

Icon::Icon(const unsigned char *const pointer, unsigned int width, unsigned int height)
    : m_Pointer(pointer), m_Width(width), m_Hight(height)
{
}

const unsigned char *Icon::getData() const
{
    return m_Pointer;
}

unsigned int Icon::getWidth() const
{
    return m_Width;
}

unsigned int Icon::getHight() const
{
    return m_Hight;
}

void Icon::animate(Adafruit_SSD1306* const pHandler, int startX, int y, int endX, unsigned int animationDelay) const
{
    if (pHandler)
    {
        const int delayPart = animationDelay / std::abs(startX - endX);
        int xPosition = startX;

        for (; xPosition <= endX; ++xPosition)
        {
            pHandler->drawBitmap(xPosition, y, m_Pointer, m_Width, m_Hight, WHITE);
            pHandler->display();
            delay(delayPart);
            pHandler->drawBitmap(xPosition, y, m_Pointer, m_Width, m_Hight, BLACK);
        }
    }
}