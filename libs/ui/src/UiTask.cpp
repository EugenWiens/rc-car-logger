
#include "UiTask.hpp"
#include "DebugOut.hpp"
#include "SplashScreen.hpp"
#include "WindowManager.hpp"

#include <Arduino.h>
#include "EventManager.hpp"

namespace {
    Adafruit_SSD1306 handler;

    WindowManager windowManager(handler);

    EventManager buttonA(D5, EventManager::InputDevice::buttonA, windowManager);
    EventManager buttonB(D6, EventManager::InputDevice::buttonB, windowManager);
}

void UiTask::setup()
{
    handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    handler.clearDisplay();

    windowManager.init();
    buttonA.init();
    buttonB.init();

    // SplashScreen splashScreen(handler);
    // splashScreen.show();
}

void UiTask::run()
{
    windowManager.show();
}
