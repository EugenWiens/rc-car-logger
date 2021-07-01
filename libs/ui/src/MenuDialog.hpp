
#pragma once

#include "UiWidget.hpp"
#include "LogConfig.hpp"
#include "EventManager.hpp"

class MenuDialog : public UiWidget
{
public:
    MenuDialog(Adafruit_SSD1306* pHandler);
    MenuDialog();

    virtual bool handleEvent(const EventManager::UiEvent &event) = 0;

    virtual String getButtonAString() const;
    virtual String getButtonBString() const;

protected:
    String getButtonStringNext() const;
    String getButtonStringEnter() const;
    String getButtonStringClear() const;
    String getButtonStringExit() const;
};