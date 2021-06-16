
#pragma once

#include "UiWidget.hpp"


class SplashScreen : public UiWidget
{
public:
    using UiWidget::UiWidget;

    void show(int x=0, int y=0) override;

private:
    void showText(uint16_t color);
};