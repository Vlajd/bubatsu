#include "bbzpch.h"
#include "RenderCommand.h"

#include "Impl/OpenGL/OpenGLRenderApi.h"


namespace Bubatsu
{
    SRef<RenderApi> RenderCommand::s_RenderApi = NewSRef<OpenGLRenderApi>();
}

