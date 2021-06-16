
#pragma once

#include "MenuDialog.hpp"
#include "LogConfig.hpp"
#include "DataLogger.hpp"


class LoggerInfoDialog : public MenuDialog
{
public:
    using GetterFunctionPointer = String (*)(const LogDragIndicator &indicator);
    struct GetterInfo
    {
        String name;
        GetterFunctionPointer getter;
    };

    LoggerInfoDialog(Adafruit_SSD1306* pHandler);
    LoggerInfoDialog();

    void setConfigIndex(int index);
    void draw(int x, int y) override;
    bool handleEvent(const EventManager::UiEvent &event) override;

    String getButtonAString() const override;
    String getButtonBString() const override;

private:
    int m_Index;
    int m_InfoIndex;

    void increaseInfoIndex();
};