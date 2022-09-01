#include "bbzpch.h"
#include "OrthographicCameraController.h"

namespace Bubatsu
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_EnableRotation(enableRotation) {}
    
    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyboardPressed(BBZ_KEY_A))
        {
            m_Position.x -= ts * m_TranslationSpeed;
        }
        if (Input::IsKeyboardPressed(BBZ_KEY_D))
        {
            m_Position.x += ts * m_TranslationSpeed;
        }
        if (Input::IsKeyboardPressed(BBZ_KEY_S))
        {
            m_Position.y -= ts * m_TranslationSpeed;
        }
        if (Input::IsKeyboardPressed(BBZ_KEY_W))
        {
            m_Position.y += ts * m_TranslationSpeed;
        }

        if (m_Rotation)
        {
            if (Input::IsKeyboardPressed(BBZ_KEY_E))
            {
                m_Rotation -= ts * m_RotationSpeed;
            }
            if (Input::IsKeyboardPressed(BBZ_KEY_Q))
            {
                m_Rotation += ts * m_RotationSpeed;
            }
        }

        m_Camera.SetPosition(m_Position);

        m_TranslationSpeed = m_ZoomLevel;
    }
    
    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BBZ_BIND_EVENT_FUNCTION(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(BBZ_BIND_EVENT_FUNCTION(OrthographicCameraController::OnWindowResized));
    }
    
    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;      // Hard Coded Zoom Speed
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f); // Hard Coded Max Zoom level
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
    
    bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}

