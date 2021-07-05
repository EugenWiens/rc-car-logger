
#pragma once

#include "UiWidget.hpp"


class SplashScreen : public UiWidget
{
public:
    using UiWidget::UiWidget;

    void draw(int x, int y) override;

private:
    void showText(uint16_t color);
};