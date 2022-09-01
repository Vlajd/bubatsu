#pragma once

#include "bbzpch.h"
#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Event/Event.h"


namespace Bubatsu
{
    struct WindowProperties
    {
        String Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(const String& title = "Bubatsu Engine", unsigned int width = 690, unsigned int height = 420)
            : Title(title), Width(width), Height(height) {}
    };

    class BUBATSU_API Window
    {
    public:
        using EventCallback = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallback& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool GetVSyncEnabled() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(const WindowProperties& properties = WindowProperties());
    };
}

