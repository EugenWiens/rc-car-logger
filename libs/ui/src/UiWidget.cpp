
#include <UiWidget.hpp>

void UiWidget::setHandler(Adafruit_SSD1306* pHandler)
{
    m_pHandler = pHandler;
}

void UiWidget::show(int x, int y)
{
    if (m_pHandler)
    {
        draw(x, y);
        m_pHandler->display();
    }
}

int UiWidget::getPointForCentering(int length1, int length2) const
{
    return std::abs(length1/2 - length2/2);
}



