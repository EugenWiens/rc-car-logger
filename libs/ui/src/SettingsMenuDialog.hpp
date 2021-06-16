
#pragma once

#include "MenuDialog.hpp"

class SettingsMenuDialog : public MenuDialog
{
public:
    using MenuDialog::MenuDialog;

    void draw(int x, int y) override;
    bool handleEvent(const EventManager::UiEvent &event) override;
};