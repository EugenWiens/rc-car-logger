
#include "LogStoreStatusDialog.hpp"
#include "IconProvider.hpp"
#include "DataLogger.hpp"

LogStoreStatusDialog::LogStoreStatusDialog(Adafruit_SSD1306* pHandler)
    : MenuDialog(pHandler), m_ShowStatus(false), m_ProgressBarMovementCounter(0)
{
}

LogStoreStatusDialog::LogStoreStatusDialog()
    : m_ShowStatus(nullptr)
{
}

void LogStoreStatusDialog::draw(int x, int y)
{
    if (m_ShowStatus)
    {
        drawStatus(x, y);
    }
    else
    {
        drawInfo(x, y);
    }
}

bool LogStoreStatusDialog::handleEvent(const EventManager::UiEvent &event)
{
    bool consumendEvent = false;

    if (EventManager::isEvent(event, EventManager::InputDevice::buttonA, EventManager::Event::press))
    {
        if (m_ShowStatus)
        {
            consumendEvent = true;
        }
    }

    if (EventManager::isEvent(event, EventManager::InputDevice::buttonB, EventManager::Event::press))
    {
        consumendEvent = true;
        m_ShowStatus = !m_ShowStatus;
        m_ProgressBarMovementCounter = 0;
    }

    return consumendEvent;
}

String LogStoreStatusDialog::getButtonAString() const
{
    String buttonString;

    if (!m_ShowStatus)
    {
        buttonString = MenuDialog::getButtonAString();
    }

    return buttonString;
}

String LogStoreStatusDialog::getButtonBString() const
{
    String buttonString;

    if (m_ShowStatus)
    {
        buttonString = getButtonStringExit();
    }
    else
    {
        buttonString = getButtonStringEnter();
    }

    return buttonString;
}

void LogStoreStatusDialog::drawInfo(int x, int y)
{
    const Icon &icon = IconProvider::getIcon(IconProvider::IconType::disk);
    const String str("storage");

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

void LogStoreStatusDialog::drawStatus(int x, int y)
{
    size_t usedEntries;
    size_t maxEntries;
    DataLogger::getInstance().getStoreStatus(usedEntries, maxEntries);
    String name("used");
    String storeStatus = String(usedEntries) + "/" + String(maxEntries);

    m_pHandler->setTextColor(WHITE);
    m_pHandler->setTextSize(1);

    m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), name.length() * 6), 0);
    m_pHandler->print(name);

    m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), storeStatus.length() * 6),
                          getPointForCentering(m_pHandler->height(), 8) - 4);
    m_pHandler->print(storeStatus);

    if(usedEntries < maxEntries - 1)
    {
        drawProgressBar(2, m_pHandler->height() - 20, m_pHandler->width() - 4, 8, (float)usedEntries / (float)maxEntries);
    }
    else
    {
        drawProgressBar(2, m_pHandler->height() - 20, m_pHandler->width() - 4, 8, 1.0f);
    }
}

void LogStoreStatusDialog::drawProgressBar( int x, int y, int width, int height, float percent)
{
    int maxFilledWidth = width - 4;
    int widthAsPercent = maxFilledWidth * percent;

    m_pHandler->drawRoundRect(x, y, width, height, 3, WHITE);
    m_pHandler->fillRoundRect(x + 2, y + 2, widthAsPercent, height - 4, 2, WHITE);

    if (std::abs(percent - 1.0f) < std::numeric_limits<float>::epsilon())
    {
        auto drawMovingLines = [&](int color) {
            for (int i=0; i < 6; ++i)
            {
                int distanceBetweenLines = 9;
                int lineXBase = x + 4 + i*distanceBetweenLines + m_ProgressBarMovementCounter;
                int lineYBase = y + 2 + 3;
                m_pHandler->drawLine(lineXBase, lineYBase, lineXBase + 3, lineYBase - 3, color);
            }
        };

        drawMovingLines(BLACK);
        if (m_ProgressBarMovementCounter++ >= 4)
        {
            m_ProgressBarMovementCounter = 0;
        }
        drawMovingLines(WHITE);
    }
}