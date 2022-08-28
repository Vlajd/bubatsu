#pragma once

#include "Bubatsu/Graphics/Input.h"


namespace Bubatsu
{
	class GlfwInput : public Input
	{
	protected:
		virtual bool IsKeyboardPressedImpl(int keyCode) override;

		virtual bool IsMouseButtonPressedImpl(int buttonCode) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}