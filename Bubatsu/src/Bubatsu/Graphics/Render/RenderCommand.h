#pragma once

#include "RenderApi.h"


namespace Bubatsu
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			m_RenderApi->Init();
		}

		inline static void SetClearColor(const FVec4& color)
		{
			m_RenderApi->SetClearColor(color);
		}

		inline static void Clear()
		{
			m_RenderApi->Clear();
		}

		inline static void DrawIndexed(const SPtr<VertexArray>& vertexArray)
		{
			m_RenderApi->DrawIndexed(vertexArray);
		}

	private:
		static RenderApi* m_RenderApi;
	};
}