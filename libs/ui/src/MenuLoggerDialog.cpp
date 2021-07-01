
#include "MenuLoggerDialog.hpp"
#include "IconProvider.hpp"
#include "DebugOut.hpp"
#include "LogConfig.hpp"
#include "DataLogger.hpp"

MenuLoggerDialog::MenuLoggerDialog(Adafruit_SSD1306* pHandler)
    : MenuDialog(pHandler), m_ViewMode(ViewMode::menuEntry), m_Index(-1), m_LoggerInfoDialog(pHandler)
{
}

MenuLoggerDialog::MenuLoggerDialog()
    : MenuLoggerDialog(nullptr)
{
}

MenuLoggerDialog::operator bool() const
{
    return DataLogger::getInstance().getLogConfig(m_Index);
}

void MenuLoggerDialog::setHandler(Adafruit_SSD1306* pHandler)
{
    UiWidget::setHandler(pHandler);
    m_LoggerInfoDialog.setHandler(pHandler);
}

void MenuLoggerDialog::setConfigIndex(int index)
{
    m_Index = index;
    m_LoggerInfoDialog.setConfigIndex(index);
}

void MenuLoggerDialog::draw(int x, int y)
{
    if (m_pHandler && (m_Index != -1))
    {
        if (m_ViewMode == ViewMode::menuEntry)
        {
            drawMenuEntry(x, y);
        }
        else
        {
            m_LoggerInfoDialog.draw(x, y);
        }
    }
}

bool MenuLoggerDialog::handleEvent(const EventManager::UiEvent &event)
{
    bool consumendEvent = false;

    if (m_ViewMode == ViewMode::menuEntry)
    {
        if (EventManager::isEvent(event, EventManager::InputDevice::buttonB, EventManager::Event::press))
        {
            m_ViewMode = ViewMode::infos;
            consumendEvent = true;
        }
    }
    else
    {
        consumendEvent = m_LoggerInfoDialog.handleEvent(event);

        if (consumendEvent == false)
        {
            if (EventManager::isEvent(event, EventManager::InputDevice::buttonB, EventManager::Event::press))
            {
                m_ViewMode = ViewMode::menuEntry;
                consumendEvent = true;
            }
        }
    }

    return consumendEvent;
}

String MenuLoggerDialog::getButtonAString() const
{
    String buttonAString;

    if (m_ViewMode == ViewMode::menuEntry)
    {
        buttonAString = MenuDialog::getButtonAString();
    }
    else
    {
        buttonAString = m_LoggerInfoDialog.getButtonAString();
    }

    return buttonAString;
}

String MenuLoggerDialog::getButtonBString() const
{
    String buttonBString;

    if (m_ViewMode == ViewMode::menuEntry)
    {
        buttonBString = getButtonStringEnter();
    }
    else
    {
        buttonBString = m_LoggerInfoDialog.getButtonBString();
    }

    return buttonBString;
}

void MenuLoggerDialog::drawMenuEntry(int x, int y)
{
    auto logConfig = DataLogger::getInstance().getLogConfig(m_Index);
    const Icon &icon = IconProvider::getIcon(logConfig.getIcon());
    const String str = logConfig.getName();

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
