
#pragma once

#include "MenuDialog.hpp"
#include "LogConfig.hpp"
#include "LoggerInfoDialog.hpp"

class MenuLoggerDialog : public MenuDialog
{
public:
    MenuLoggerDialog(Adafruit_SSD1306* pHandler);
    MenuLoggerDialog();

    operator bool() const;

    void setHandler(Adafruit_SSD1306* pHandler) override;
    void setConfigIndex(int index);
    void draw(int x, int y) override;
    bool handleEvent(const EventManager::UiEvent &event) override;

    String getButtonAString() const override;
    String getButtonBString() const override;
private:
    enum class ViewMode
    {
        menuEntry,
        infos
    };

    ViewMode m_ViewMode;
    int m_Index;
    LoggerInfoDialog m_LoggerInfoDialog;

    void drawMenuEntry(int x, int y);
};