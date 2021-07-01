
#pragma once

#include "MenuDialog.hpp"

class SoftwareVersionDialog : public MenuDialog
{
public:
    using MenuDialog::MenuDialog;

    void draw(int x, int y) override;
    bool handleEvent(const EventManager::UiEvent &event) override;
    String getButtonBString() const override;

private:
    bool m_ShowVersion;

    void drawInfo(int x, int y);
    void drawVersion(int x, int y);
};
