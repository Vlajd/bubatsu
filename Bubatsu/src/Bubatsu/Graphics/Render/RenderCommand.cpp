#include "bbzpch.h"
#include "RenderCommand.h"

#include "Impl/OpenGL/OpenGLRenderApi.h"


namespace Bubatsu
{
    RenderApi* RenderCommand::m_RenderApi = new OpenGLRenderApi;
}

