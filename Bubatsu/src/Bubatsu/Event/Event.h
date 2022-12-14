#pragma once

#include "bbzpch.h"
#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
    #define EVENT_CLASS(eventClass) static EventClass GetStaticClass() { return EventClass::##eventClass; }\
                                    virtual EventClass GetClass() const override { return GetStaticClass(); }\
                                    virtual const char* GetName() const override { return #eventClass; }

    #define EVENT_CATEGORY(category) virtual int GetCategory() const override { return category; }


    class BUBATSU_API Event
    {
    public:
        enum EventClass
        {
            ApplicationRendered, ApplicationTicked, ApplicationUpdated,
            KeyboardPressed, KeyboardReleased, KeyboardTyped,
            MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
            WindowClosed, WindowFocused, WindowLostFocus, WindowMoved, WindowResized
        };

        enum EventCategory
        {
            EventCategoryApplication = BIT(0),
            EventCategoryInput = BIT(1),
            EventCategoryKeyboard = BIT(2),
            EventCategoryMouse = BIT(3),
            EventCategoryMouseButton = BIT(4)
        };

        bool Handled = false;

        virtual EventClass GetClass() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategory() const = 0;
        virtual String AsString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategory() & category;
        }

        inline bool IsInClass(EventClass eclass)
        {
            return GetClass() == eclass;
        }
    };

    class BUBATSU_API EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& function)
        {
            if (m_Event.GetClass() == T::GetStaticClass())
            {
                m_Event.Handled = function(*(T*)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.AsString();
    }
}

