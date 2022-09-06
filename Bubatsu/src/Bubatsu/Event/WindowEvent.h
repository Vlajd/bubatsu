#pragma once

#include "Event.h"


namespace Bubatsu
{

    class BUBATSU_API WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height) {}

        inline uint32_t GetWidth() const { return m_Width; }
        inline uint32_t GetHeight() const { return m_Height; }

        String AsString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS(WindowResized)
        EVENT_CATEGORY(EventCategoryApplication)

    private:
        uint32_t m_Width, m_Height;
    };

    class BUBATSU_API WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() {}

        EVENT_CLASS(WindowClosed)
        EVENT_CATEGORY(EventCategoryApplication)
    };
}
