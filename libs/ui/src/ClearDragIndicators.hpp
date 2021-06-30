
#pragma once

#include "MenuDialog.hpp"

class ClearDragIndicators : public MenuDialog
{
public:
    using MenuDialog::MenuDialog;

    void draw(int x, int y) override;
    bool handleEvent(const EventManager::UiEvent &event) override;
    String getButtonBString() const override;

private:
    bool m_ShowOk;
    int m_ShowOkCounter;

    void drawCheckmark(int x, int y);

};