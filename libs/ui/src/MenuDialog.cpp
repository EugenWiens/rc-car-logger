
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
    return getButtonStringNext();
}

String MenuDialog::getButtonBString() const
{
    return getButtonStringEnter();
}

String MenuDialog::getButtonStringNext() const
{
    return String("<-");
}

String MenuDialog::getButtonStringEnter() const
{
    return String("EN");
}

String MenuDialog::getButtonStringClear() const
{
    return String("CL");
}

String MenuDialog::getButtonStringExit() const
{
    return String("EX");
}