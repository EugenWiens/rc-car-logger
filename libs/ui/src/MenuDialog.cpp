
#include "MenuDialog.hpp"


MenuDialog::MenuDialog(Adafruit_SSD1306 *pHandler)
    : UiWidget(pHandler)
{
}

MenuDialog::MenuDialog()
    : MenuDialog(nullptr)
{
}

String MenuDialog::getButtonAString() const
{
    return String("<-");
}

String MenuDialog::getButtonBString() const
{
    return String("EN");
}