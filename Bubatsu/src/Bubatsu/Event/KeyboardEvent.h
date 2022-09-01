#pragma once

#include "Event.h"


namespace Bubatsu
{
    class BUBATSU_API KeyboardEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyboardEvent(int keyCode)
            : m_KeyCode(keyCode) {}

        int m_KeyCode;
    };

    class BUBATSU_API KeyboardPressedEvent : public KeyboardEvent
    {
    public:
        KeyboardPressedEvent(int keyCode, int repeatCount)
            : KeyboardEvent(keyCode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return  m_RepeatCount; }

        String AsString() const override
        {
            std::stringstream ss;
            ss << "keyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS(KeyboardPressed)

    private:
        int m_RepeatCount;
    };

    class BUBATSU_API KeyboardReleasedEvent : public KeyboardEvent
    {
    public:
        KeyboardReleasedEvent(int keyCode)
            : KeyboardEvent(keyCode) {}

        String AsString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS(KeyboardReleased)
    };

    class BUBATSU_API KeyboardTypedEvent : public KeyboardEvent
    {
    public:
        KeyboardTypedEvent(int keyCode)
            : KeyboardEvent(keyCode) {}

        String AsString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS(KeyboardTyped)

    private:
        int m_RepeatCount;
    };
}