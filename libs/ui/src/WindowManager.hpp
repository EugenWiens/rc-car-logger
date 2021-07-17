
#pragma once

#include "UiWidget.hpp"
#include "stddef.h"
#include <Adafruit_SSD1306.h>
#include <array>
#include "MenuDialog.hpp"
#include "MenuLoggerDialog.hpp"
#include "EventManager.hpp"


class WindowManager
{
public:
    static constexpr size_t m_extraWidgetSize = 3;

    WindowManager(Adafruit_SSD1306& handler);

    void init();

    void handleEvent(const EventManager::UiEvent& event);
    void show();

private:
    using MenuLoggerDialogArray = std::array<MenuLoggerDialog, LOG_CONFIG_STORE_SIZE>;
    using MenuDialogArray = std::array<MenuDialog*, LOG_CONFIG_STORE_SIZE + m_extraWidgetSize>;

    Adafruit_SSD1306& m_Handler;
    MenuDialogArray m_AllMenuDialogArray;
    MenuLoggerDialogArray m_MenuLoggerDialogArray;

    unsigned int m_CurrentDialogIndex;
    unsigned int m_ValideDialogs;

    void drawControllArea();
    String getButtonAString() const;
    String getButtonBString() const;
    String getScrollBar() const;
    MenuDialog& getCurrentDialog();
    void increaseDialogIndex();

    void addDialog(MenuDialog& dialog);
    void addLoggerDialogs();
    unsigned int calculatePages();
};