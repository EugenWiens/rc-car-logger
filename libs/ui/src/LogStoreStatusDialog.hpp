
#pragma once

#include "MenuDialog.hpp"

class LogStoreStatusDialog : public MenuDialog
{
public:
    LogStoreStatusDialog(Adafruit_SSD1306* pHandler);
    LogStoreStatusDialog();

    void draw(int x, int y) override;
    bool handleEvent(const EventManager::UiEvent &event) override;
    String getButtonAString() const override;
    String getButtonBString() const override;

private:
    bool m_ShowStatus;
    int m_ProgressBarMovementCounter;
    void drawInfo(int x, int y);
    void drawStatus(int x, int y);
    void drawProgressBar( int x, int y, int width, int height, float percent);
};
