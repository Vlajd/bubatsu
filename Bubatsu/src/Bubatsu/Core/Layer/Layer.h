#pragma once

#include "Bubatsu/Core/Core.h"
#include "Bubatsu/Core/Timestep.h"
#include "Bubatsu/Event/Event.h"


namespace Bubatsu
{
    class BUBATSU_API Layer
    {
    public:
        Layer(const String& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const String& GetDebugName() const { return m_DebugName; }

    protected:
        String m_DebugName;
    };
}

