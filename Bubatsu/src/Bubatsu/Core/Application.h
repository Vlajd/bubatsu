#pragma once

#include "Bubatsu/Graphics/Window.h"
#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Core/Timestep.h"
#include "Bubatsu/Event/Event.h"
#include "Bubatsu/Event/ApplicationEvent.h"
#include "Bubatsu/ImGui/ImGuiLayer.h"
#include "Bubatsu/Core/Layer/LayerStack.h"


namespace Bubatsu
{
    class BUBATSU_API Application
    {
    public:

        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClosed(WindowClosedEvent& e);
        bool OnWindowResized(WindowResizedEvent& e);

        UPtr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
        bool m_Minimized = false;

        static Application* s_Instance;
    };

    // defined in client
    Application* BubatsuMain();
}

