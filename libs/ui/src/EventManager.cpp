
#include "EventManager.hpp"
#include "Arduino.h"
#include "TimeProvider.hpp"
#include "WindowManager.hpp"

EventManager::EventManager(int pinNumber, InputDevice inputDevice, WindowManager &windowManager)
    : m_Timestamp(0), m_PinNumber(pinNumber), m_InputDevice(inputDevice), m_WindowManager(windowManager)
{
}

void EventManager::init()
{
    pinMode(m_PinNumber, INPUT_PULLUP);
    attachInterruptArg(m_PinNumber, EventManager::interrupt, this, CHANGE);
}

void EventManager::setPressed()
{
    m_Timestamp = TimeProvider::getInstance().now();
}

void EventManager::setReleased()
{
    unsigned int releasedTime = m_Timestamp = TimeProvider::getInstance().now();

    emitEvent(releasedTime - m_Timestamp);
}

int EventManager::getPinNumber() const
{
    return m_PinNumber;
}

void EventManager::interrupt(void *arg)
{
    EventManager *pEventManager = static_cast<EventManager *>(arg);
    if (pEventManager)
    {
        if (digitalRead(pEventManager->getPinNumber()) == 0)
        {
            pEventManager->setPressed();
        }
        else
        {
            pEventManager->setReleased();
        }
    }
}

void EventManager::emitEvent(unsigned int pressTimePeriod)
{
    UiEvent event = {
        .inputDevice = m_InputDevice};

    if (pressTimePeriod < 200)
    {
        event.event = Event::press;
    }
    else
    {
        event.event = Event::longPress;
    }

    m_WindowManager.handleEvent(event);
}

bool EventManager::isEvent(const UiEvent &eventStruct, const InputDevice& inputDevice, const Event& event)
{
    bool eventMatch = false;

    if ((eventStruct.inputDevice == inputDevice) &&
        (eventStruct.event == event))
    {
        eventMatch = true;
    }

    return eventMatch;
}