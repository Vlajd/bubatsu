#pragma once

#include "bbzpch.h"
#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Event/Event.h"


namespace Bubatsu
{
    struct WindowProperties
    {
        String Title;
        uint32_t Width;
        uint32_t Height;

        WindowProperties(const String& title = "Bubatsu Engine", uint32_t width = 690, uint32_t height = 420)
            : Title(title), Width(width), Height(height) {}
    };

    class BUBATSU_API Window
    {
    public:
        using EventCallback = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallback& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool GetVSyncEnabled() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static URef<Window> Create(const WindowProperties& properties = WindowProperties());
    };
}

