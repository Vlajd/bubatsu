#pragma once

#include "Bubatsu/Core/Core.h"


namespace Bubatsu {

    class BUBATSU_API Input
    {
    public:
        inline static bool IsKeyboardPressed(int keyCode) { return s_Instance->IsKeyboardPressedImpl(keyCode); }

        inline static bool IsMouseButtonPressed(int buttonCode) { return s_Instance->IsMouseButtonPressedImpl(buttonCode); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        virtual bool IsKeyboardPressedImpl(int keyCode) = 0;

        virtual bool IsMouseButtonPressedImpl(int buttonCode) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static Input* s_Instance;
    };
}