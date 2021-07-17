
#include "SoftwareVersionDialog.hpp"
#include "IconProvider.hpp"
#include "DataLogger.hpp"

SoftwareVersionDialog::SoftwareVersionDialog(Adafruit_SSD1306* pHandler)
    : MenuDialog(pHandler), m_ShowVersion(false)
{
}

SoftwareVersionDialog::SoftwareVersionDialog()
    : SoftwareVersionDialog(nullptr)
{
}

void SoftwareVersionDialog::draw(int x, int y)
{
    if (m_ShowVersion)
    {
        drawVersion(x, y);
    }
    else
    {
        drawInfo(x, y);
    }
}

bool SoftwareVersionDialog::handleEvent(const EventManager::UiEvent &event)
{
    bool consumendEvent = false;

    if (EventManager::isEvent(event, EventManager::InputDevice::buttonA, EventManager::Event::press))
    {
        if (m_ShowVersion)
        {
            consumendEvent = true;
        }
    }

    if (EventManager::isEvent(event, EventManager::InputDevice::buttonB, EventManager::Event::press))
    {
        consumendEvent = true;
        m_ShowVersion = !m_ShowVersion;
    }

    return consumendEvent;
}

String SoftwareVersionDialog::getButtonAString() const
{
    String buttonString;

    if (!m_ShowVersion)
    {
        buttonString = MenuDialog::getButtonAString();
    }

    return buttonString;
}

String SoftwareVersionDialog::getButtonBString() const
{
    String buttonString;

    if (m_ShowVersion)
    {
        buttonString = getButtonStringExit();
    }
    else
    {
        buttonString = getButtonStringEnter();
    }

    return buttonString;
}

void SoftwareVersionDialog::drawInfo(int x, int y)
{
    const Icon &icon = IconProvider::getIcon(IconProvider::IconType::info);
    const String str("sw version");

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

void SoftwareVersionDialog::drawVersion(int x, int y)
{
    String name("version");
    String version(VERSION_TAG);

    m_pHandler->setTextColor(WHITE);
    m_pHandler->setTextSize(1);

    m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), name.length() * 6), 0);
    m_pHandler->print(name);

    m_pHandler->setCursor(getPointForCentering(m_pHandler->width(), version.length() * 6),
                          getPointForCentering(m_pHandler->height(), 8) - 4);
    m_pHandler->print(version);
}