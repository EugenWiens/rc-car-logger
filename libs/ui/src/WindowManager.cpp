
#include "WindowManager.hpp"
#include "DataLogger.hpp"

WindowManager::WindowManager(Adafruit_SSD1306 &handler)
    : m_Handler(handler), m_AllMenuDialogArray{}, m_CurrentDialogIndex(0), m_ValideDialogs(0)
{
}

void WindowManager::init()
{
    addLoggerDialogs();
}

void WindowManager::handleEvent(const EventManager::UiEvent &event)
{
    bool eventHandelt = getCurrentDialog().handleEvent(event);

    if (eventHandelt == false)
    {
        if (false == getCurrentDialog().handleEvent(event))
        {
            if (EventManager::isEvent(event, EventManager::InputDevice::buttonA, EventManager::Event::press))
            {
                increaseDialogIndex();
            }
        }
    }
}

void WindowManager::show()
{
    m_Handler.clearDisplay();

    getCurrentDialog().draw(0, 0);
    drawControllArea();

    m_Handler.display();
}

void WindowManager::drawControllArea()
{
    m_Handler.setTextSize(1);
    m_Handler.setTextColor(WHITE);
    m_Handler.setCursor(0, m_Handler.height() - 8);
    m_Handler.print(getCurrentDialog().getButtonAString() + " " + getScrollBar() + " " + getCurrentDialog().getButtonBString());
}

String WindowManager::getScrollBar() const
{
    const unsigned int elementsOnPage = 4;
    unsigned int pages = m_ValideDialogs / elementsOnPage;
    unsigned int positionInPage = m_CurrentDialogIndex % elementsOnPage;
    unsigned int positionOnPage = m_CurrentDialogIndex / elementsOnPage;
    String scrollBar("----");

    scrollBar[positionInPage] = '=';

    return scrollBar;
}

MenuDialog& WindowManager::getCurrentDialog()
{
    return *m_AllMenuDialogArray[m_CurrentDialogIndex];
}

void WindowManager::increaseDialogIndex()
{
    m_CurrentDialogIndex = (m_CurrentDialogIndex + 1) % m_ValideDialogs;
}

void WindowManager::addDialog(MenuDialog& dialog)
{
    bool added = false;

    for (auto & pDialog: m_AllMenuDialogArray)
    {
        if (pDialog == nullptr)
        {
            debugLog() << "add dialog";

            pDialog = &dialog;
            added = true;
            m_ValideDialogs++;

            break;
        }
    }

    if (added == false)
    {
        debugLog() << "can't add the dialog";
    }
}

void WindowManager::addLoggerDialogs()
{
    auto dataArray = DataLogger::getInstance().getLogDataArray();

    for (int indexId = 0; indexId < dataArray.size(); ++indexId)
    {
        MenuLoggerDialog& dialog = m_MenuLoggerDialogArray[indexId];
        dialog.setHandler(&m_Handler);
        dialog.setConfigIndex(indexId);

        if (dialog)
        {
            addDialog(dialog);
        }
    }
}