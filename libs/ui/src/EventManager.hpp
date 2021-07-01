#pragma once

class WindowManager;

class EventManager
{
public:
    enum class InputDevice
    {
        buttonA,
        buttonB
    };

    enum class Event
    {
        press,
        longPress
    };

    struct UiEvent
    {
        InputDevice inputDevice;
        Event event;
    };

    EventManager(int pinNumber, InputDevice inputDevice, WindowManager& windowManager);

    void init();
    void setPressed();
    void setReleased();
    int getPinNumber() const;

    static void interrupt(void* arg);
    static bool isEvent(const UiEvent& eventStruct, const InputDevice& inputDevice, const Event& event);

private:
    unsigned int m_Timestamp;
    int m_PinNumber;
    InputDevice m_InputDevice;
    WindowManager& m_WindowManager;

    void emitEvent(unsigned int pressTimePeriod);
};