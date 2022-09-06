#include "bbzpch.h"
#include "Application.h"

#include "Bubatsu/Graphics/Core/Renderer.h"

#include <GLFW/glfw3.h>


namespace Bubatsu
{
    #define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        BBZ_PROFILE_FUNCTION();

        BBZ_CORE_ASSERT(s_Instance, "Application Already Exists!")
            s_Instance = this;

        m_Window = URef<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        BBZ_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        BBZ_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        BBZ_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        BBZ_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FUNCTION(OnWindowClosed));
        dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNCTION(OnWindowResized));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
            {
                break;
            }
        }
    }

    void Application::Run()
    {
        BBZ_PROFILE_FUNCTION();

        do
        {
            BBZ_PROFILE_SCOPE("MainLoop");

            float time = (float)glfwGetTime(); // Platform::GetTime
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized)
            {
                {
                    BBZ_PROFILE_SCOPE("LayerStack OnUpdate");

                    for (Layer* layer : m_LayerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
                }

                // ImGui
                m_ImGuiLayer->Begin();
                {
                    BBZ_PROFILE_SCOPE("LayerStack OnImGuiRender");

                    for (Layer* layer : m_LayerStack)
                    {
                        layer->OnImGuiRender();
                    }
                }
                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
        while (m_Running);
    }

    bool Application::OnWindowClosed(WindowClosedEvent& e)
    {
        m_Running = false;
        return true;
    }
    bool Application::OnWindowResized(WindowResizedEvent& e)
    {
        BBZ_PROFILE_FUNCTION();

        uint32_t width = e.GetWidth();
        uint32_t height = e.GetHeight();
        if (width == 0 || height == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResized(width, height);

        return false;
    }
}

