
#include "LoggerInfoDialog.hpp"

namespace
{
    constexpr int maxInfoEntries = 3;

    LoggerInfoDialog::GetterInfo getterInfo[maxInfoEntries] = {
        {
            .name = "last",
            .getter = [](const LogDragIndicator &indicator) -> String { return indicator.getLast().toString(); }
        },
        {
            .name = "min",
            .getter = [](const LogDragIndicator &indicator) -> String { return indicator.getMin().toString(); }
        },
        {
            .name = "max",
            .getter = [](const LogDragIndicator &indicator) -> String { return indicator.getMax().toString(); }
        }
    };

}

LoggerInfoDialog::LoggerInfoDialog(Adafruit_SSD1306 *pHandler)
    : MenuDialog(pHandler), m_Index(-1), m_InfoIndex(0)
{
}

LoggerInfoDialog::LoggerInfoDialog()
    : LoggerInfoDialog(nullptr)
{
}

void LoggerInfoDialog::setConfigIndex(int index)
{
    m_Index = index;
}

void LoggerInfoDialog::draw(int x, int y)
{
    if (m_pHandler)
    {
        auto logConfig = DataLogger::getInstance().getLogConfig(m_Index);

        if (logConfig)
        {
            auto dragIndicator = DataLogger::getInstance().getLogDragIndicator(m_Index);
            String name = getterInfo[m_InfoIndex].name;
            String unit = logConfig.getUnit();
            String value = getterInfo[m_InfoIndex].getter(dragIndicator);

            m_pHandler->setTextColor(WHITE);
            m_pHandler->setTextSize(1);

            m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), name.length() * 6), 0);
            m_pHandler->print(name);

            m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), value.length() * 6),
                                  getPointForCentering(m_pHandler->height(), 8) - 4);
            m_pHandler->print(value);

            m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), unit.length() * 6),
                                  getPointForCentering(m_pHandler->height(), 8) + 8);
            m_pHandler->print(unit);
        }
    }
}

bool LoggerInfoDialog::handleEvent(const EventManager::UiEvent &event)
{
    bool consumendEvent = false;

    if (EventManager::isEvent(event, EventManager::InputDevice::buttonA, EventManager::Event::press))
    {
        consumendEvent = true;
        increaseInfoIndex();
    }

    return consumendEvent;
}

String LoggerInfoDialog::getButtonAString() const
{
    return MenuDialog::getButtonAString();
}

String LoggerInfoDialog::getButtonBString() const
{
    return getButtonStringExit();
}

void LoggerInfoDialog::increaseInfoIndex()
{
    m_InfoIndex++;
    m_InfoIndex %= maxInfoEntries;
}
