#pragma once

#include "OrthographicCamera.h"
#include "Bubatsu/Core/Math.h"
#include "Bubatsu/Core/Timestep.h"
#include "Bubatsu/Core/Codes.h"
#include "Bubatsu/Graphics/Input.h"
#include "Bubatsu/Event/WindowEvent.h"
#include "Bubatsu/Event/MouseEvent.h"

namespace Bubatsu
{
    class BUBATSU_API OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool enableRotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event&);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        void SetZoomLevel(float level) { m_ZoomLevel = level; }
        float GetZoomLevel() const { return m_ZoomLevel; }

        void SetPosition(FVec3 position) { m_Position = position; }
        FVec3 GetPosition() const { return m_Position; }

        void SetRotation(float rotation) { m_Rotation = rotation; }
        float GetRotation() const { return m_Rotation; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizedEvent& e);

        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
        bool m_EnableRotation;
        FVec3 m_Position = FVec3(0.0f, 0.0f, 0.0f);
        float m_Rotation = 0.0f;
        float m_TranslationSpeed = 5.0f, m_RotationSpeed = 160.0f;
    };
}

