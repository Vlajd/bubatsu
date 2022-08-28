#pragma once

#include "Bubatsu/Graphics/Render/RenderApi.h"


namespace Bubatsu
{
	class OpenGLRenderApi : public RenderApi
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const FVec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const SPtr<VertexArray>& vertexArray) override;
	};
}

