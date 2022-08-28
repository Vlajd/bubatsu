#include "bbzpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Impl/OpenGL/OpenGLTexture.h"


namespace Bubatsu
{
	SPtr<Texture2D> Texture2D::Create(const String& path) 
	{
		switch (Renderer::GetApi())
		{
		case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
		case RenderApi::Api::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		BBZ_CORE_ASSERT(true, "VertexArray::Unknown RenderApi!");
		return nullptr;
	}
}