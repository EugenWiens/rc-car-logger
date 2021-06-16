
#include "SplashScreen.hpp"

#include "IconProvider.hpp"
#include "Icon.hpp"


void SplashScreen::show(int x, int y)
{
    if (m_pHandler)
    {
        const Icon& icon = IconProvider::getIcon(IconProvider::IconType::rccar);
        const int endXPoint = getPointForCentering( m_pHandler->width(), icon.getWidth());

        icon.animate(m_pHandler, -icon.getWidth(), 0, endXPoint, 100);

        showText(WHITE);
        delay(2000);
        showText(BLACK);

        icon.animate(m_pHandler, endXPoint, 0, m_pHandler->width(), 100);
    }
}

void SplashScreen::showText(uint16_t color)
{
    if (m_pHandler)
    {
        m_pHandler->setTextSize(1);
        m_pHandler->setTextColor(color);
        m_pHandler->setCursor(14, 20);
        m_pHandler->println("RC Car");
        m_pHandler->setCursor(14, 30);
        m_pHandler->println("Logger");
        m_pHandler->display();
    }
}