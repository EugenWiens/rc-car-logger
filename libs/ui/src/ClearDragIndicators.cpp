
#include "ClearDragIndicators.hpp"
#include "IconProvider.hpp"
#include "DataLogger.hpp"

void ClearDragIndicators::draw(int x, int y)
{
    if (m_ShowOkCounter > 0)
    {
        drawCheckmark(x, y);
        m_ShowOkCounter--;
    }
    else
    {
        const Icon &icon = IconProvider::getIcon(IconProvider::IconType::garbage);
        const String str("Indicators");

        m_pHandler->drawBitmap(getPointForCentering(m_pHandler->width(), icon.getWidth()),
                               getPointForCentering(m_pHandler->height(), icon.getHight()),
                               icon.getData(),
                               icon.getWidth(),
                               icon.getHight(),
                               WHITE);

        m_pHandler->setTextSize(1);
        m_pHandler->setTextColor(WHITE);
        m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), str.length() * 6), 0);
        m_pHandler->print(str);
    }
}

bool ClearDragIndicators::handleEvent(const EventManager::UiEvent &event)
{
    bool consumendEvent = false;

    if (m_ShowOkCounter > 0)
    {
        consumendEvent = true;
    }
    else
    {
        if (EventManager::isEvent(event, EventManager::InputDevice::buttonB, EventManager::Event::press))
        {
            DataLogger::getInstance().clearAllDragIndicators();
            consumendEvent = true;
            m_ShowOkCounter = 10;
        }
    }

    return consumendEvent;
}

String ClearDragIndicators::getButtonBString() const
{
    return String("DL");
}

void ClearDragIndicators::drawCheckmark(int x, int y)
{
    const Icon &icon = IconProvider::getIcon(IconProvider::IconType::checkmark);
    const String str("done");

    m_pHandler->drawBitmap(getPointForCentering(m_pHandler->width(), icon.getWidth()),
                           getPointForCentering(m_pHandler->height(), icon.getHight()),
                           icon.getData(),
                           icon.getWidth(),
                           icon.getHight(),
                           WHITE);

    m_pHandler->setTextSize(1);
    m_pHandler->setTextColor(WHITE);
    m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), str.length() * 6), 0);
    m_pHandler->print(str);
}