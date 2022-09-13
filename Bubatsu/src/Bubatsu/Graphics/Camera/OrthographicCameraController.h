#pragma once

#include "OrthographicCamera.h"
#include "Bubatsu/Core/Math.h"
#include "Bubatsu/Core/Timestep.h"
#include "Bubatsu/Core/Codes.h"
#include "Bubatsu/Graphics/Input.h"
#include "Bubatsu/Event/WindowEvent.h"
#include "Bubatsu/Event/MouseButtonEvent.h"
#include "Bubatsu/Event/MouseEvent.h"

namespace Bubatsu
{
    class BUBATSU_API OrthographicCameraController
    {
    public:
        struct ZoomData
        {
            float Level = 1.0f;
            float Target = 1.0f;
            float Speed = 0.45f;
            float LSpeed = 15.0f;
            float Min = 0.25f;
            float Max = 512.0f;
        };

        struct TranslateData
        {
            FVec3 Position = FVec3(0.0f);
            FVec3 Target = FVec3(0.0f);
            FVec2 StartMouse = FVec2(0.0f);
            bool MouseDown = false;
            float Speed = 2.5f;
            float LSpeed = 17.5f;
            float ZSpeed = 0.0f;
        };

        OrthographicCameraController(float aspectRatio);

        void OnUpdate(Timestep ts);
        void OnEvent(Event&);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        void SetZoom(ZoomData data) { m_Zoom = data; }
        ZoomData GetZoom() const { return m_Zoom; }

        void SetTranslate(TranslateData data) { m_Translate = data; }
        TranslateData GetTranslate() const { return m_Translate; }

    private:
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizedEvent& e);

        ZoomData m_Zoom;
        TranslateData m_Translate;
        float m_AspectRatio;
        OrthographicCamera m_Camera;
    };
}

