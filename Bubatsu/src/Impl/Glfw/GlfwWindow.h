#pragma once

#include "Bubatsu/Graphics/Window.h"
#include "Bubatsu/Graphics/Core/Context.h"

#include <GLFW/glfw3.h>


namespace Bubatsu
{
    class BUBATSU_API GlfwWindow : public Window
    {
    public:
        GlfwWindow(const WindowProperties& properties);
        virtual ~GlfwWindow();

        void OnUpdate() override;

        inline uint32_t GetWidth() const override { return m_Data.Width; };
        inline uint32_t GetHeight() const override { return m_Data.Height; };

        // Window Attributes
        inline void SetEventCallback(const EventCallback& callback) override
        {
            m_Data.EventCallback = callback;
        };

        void SetVSync(bool enabled) override;
        bool GetVSyncEnabled() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; };

    private:
        virtual void Init(const WindowProperties& properties);
        virtual void ShutDown();

        GLFWwindow* m_Window;
        URef<Context> m_Context;

        struct WindowData
        {
            String Title;
            uint32_t Width, Height;
            bool VSync;

            EventCallback EventCallback;
        };

        WindowData m_Data;

        static unsigned short s_WindowCount;
    };
}

