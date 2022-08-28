#pragma once

#include "Shader.h"
#include "RenderCommand.h"
#include "Bubatsu/Graphics/Camera/OrthographicCamera.h"


namespace Bubatsu
{
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera); // [TODO] Get other Params
		static void EndScene();

		static void Submit(const SPtr<Shader>& shader, const SPtr<VertexArray>& vertexArray, const FMat4& transform = FMat4(1.0f));

		inline static RenderApi::Api GetApi()
		{
			return RenderApi::GetApi();
		}

	private:
		struct SceneData
		{
			FMat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}