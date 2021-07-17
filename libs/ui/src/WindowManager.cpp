
#include "WindowManager.hpp"
#include "DataLogger.hpp"
#include "ClearDragIndicators.hpp"
#include "SoftwareVersionDialog.hpp"
#include "LogStoreStatusDialog.hpp"
#include "DebugOut.hpp"

namespace
{
    ClearDragIndicators settingsDialog;
    SoftwareVersionDialog softwareVersionDialog;
    LogStoreStatusDialog logStoreStatusDialog;

    MenuDialog* extraDialogs[WindowManager::m_extraWidgetSize] = {
        &logStoreStatusDialog,
        &settingsDialog,
        &softwareVersionDialog,
    };
}

WindowManager::WindowManager(Adafruit_SSD1306 &handler)
    : m_Handler(handler), m_AllMenuDialogArray{}, m_CurrentDialogIndex(0), m_ValideDialogs(0)
{
}

void WindowManager::init()
{
    addLoggerDialogs();

    for (auto& dialog : extraDialogs)
    {
        dialog->setHandler(&m_Handler);
        addDialog(*dialog);
    }
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
    m_Handler.print(getCurrentDialog().getButtonAString());

    m_Handler.setCursor(3 * 6, m_Handler.height() - 8);
    m_Handler.print(getScrollBar());

    m_Handler.setCursor(m_Handler.width() - 3 * 6, m_Handler.height() - 8);
    m_Handler.print(getCurrentDialog().getButtonBString());
}

String WindowManager::getScrollBar() const
{
    String scrollBar;

    const unsigned int elementsOnPage = 4;
    unsigned int elementsOnLastPage = m_ValideDialogs % elementsOnPage;
    unsigned int positionInPage = m_CurrentDialogIndex % elementsOnPage;
    unsigned int startOfLastPage = m_ValideDialogs - elementsOnLastPage;
    unsigned int printableElements = 0;

    if (m_CurrentDialogIndex >= startOfLastPage)
    {
        printableElements = elementsOnLastPage;
    }
    else
    {
        printableElements = elementsOnPage;
    }

    for (int i=0; i < printableElements; ++i)
    {
        scrollBar += "-";
    }

    scrollBar[positionInPage] = '=';

    return scrollBar;
}

MenuDialog &WindowManager::getCurrentDialog()
{
    return *m_AllMenuDialogArray[m_CurrentDialogIndex];
}

void WindowManager::increaseDialogIndex()
{
    m_CurrentDialogIndex = (m_CurrentDialogIndex + 1) % m_ValideDialogs;
}

void WindowManager::addDialog(MenuDialog &dialog)
{
    bool added = false;

    for (auto &pDialog : m_AllMenuDialogArray)
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
        MenuLoggerDialog &dialog = m_MenuLoggerDialogArray[indexId];
        dialog.setHandler(&m_Handler);
        dialog.setConfigIndex(indexId);

        if (dialog)
        {
            addDialog(dialog);
        }
    }
}

unsigned int WindowManager::calculatePages()
{
    const unsigned int elementsOnPage = 4;
    unsigned int pages = m_ValideDialogs / elementsOnPage;

    if (m_ValideDialogs % elementsOnPage)
    {
        pages += 1;
    }

    return pages;
}
