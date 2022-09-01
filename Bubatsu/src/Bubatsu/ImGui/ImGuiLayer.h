#pragma once

#include "Bubatsu/Core/Layer/Layer.h"

#include "Bubatsu/Event/Event.h"
#include "Bubatsu/Event/KeyboardEvent.h"
#include "Bubatsu/Event/MouseEvent.h"
#include "Bubatsu/Event/MouseButtonEvent.h"
#include "Bubatsu/Event/WindowEvent.h"
#include "Bubatsu/Event/ApplicationEvent.h"


namespace Bubatsu {

    class BUBATSU_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };
}