#include "bbzpch.h"
#include "OrthographicCameraController.h"

namespace Bubatsu
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_Zoom.Level, m_AspectRatio * m_Zoom.Level, -m_Zoom.Level, m_Zoom.Level)
    {
        BBZ_PROFILE_FUNCTION();
    }
    
    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        BBZ_PROFILE_FUNCTION();

        // ====================================================
        // Zoom
        // ====================================================
        m_Zoom.Level += (m_Zoom.Target - m_Zoom.Level) * m_Zoom.LSpeed * ts;
        m_Camera.SetProjection(-m_AspectRatio * m_Zoom.Level, m_AspectRatio * m_Zoom.Level, -m_Zoom.Level, m_Zoom.Level);

        // ====================================================
        // Translate
        // ====================================================
        m_Translate.ZSpeed = (m_Zoom.Level + m_Zoom.Min) / m_Zoom.Max * m_Translate.Speed;
        m_Translate.Position += (m_Translate.Target - m_Translate.Position) * m_Translate.LSpeed * FVec3(ts);
        m_Camera.SetPosition(m_Translate.Position);
    }
    
    void OrthographicCameraController::OnEvent(Event& e)
    {
        BBZ_PROFILE_FUNCTION();

        if (e.IsInClass(Event::MouseButtonPressed)) { m_Translate.MouseDown = true; }
        if (e.IsInClass(Event::MouseButtonReleased)) { m_Translate.MouseDown = false; }

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseMovedEvent>(BBZ_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseMoved));
        dispatcher.Dispatch<MouseScrolledEvent>(BBZ_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(BBZ_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseMoved(MouseMovedEvent& e)
    {
        BBZ_PROFILE_FUNCTION();

        if (m_Translate.MouseDown)
        {
            m_Translate.Target += FVec3(-(e.GetX() - m_Translate.StartMouse.x), e.GetY() - m_Translate.StartMouse.y, 0.0f) * m_Translate.ZSpeed;
        }
        m_Translate.StartMouse = FVec2(e.GetX(), e.GetY());

        return false;
    }
    
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        BBZ_PROFILE_FUNCTION();

        m_Zoom.Target -= e.GetYOffset() * m_Zoom.Speed;
        m_Zoom.Target = std::max(m_Zoom.Target, m_Zoom.Min);
        m_Zoom.Target = std::min(m_Zoom.Target, m_Zoom.Max);

        return false;
    }
    
    bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& e)
    {
        BBZ_PROFILE_FUNCTION();

        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_Zoom.Level, m_AspectRatio * m_Zoom.Level, -m_Zoom.Level, m_Zoom.Level);
        return false;
    }
}

