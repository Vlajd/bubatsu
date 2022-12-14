#include "bbzpch.h"
#include "Shader.h"

#include "Bubatsu/Graphics/Core/Renderer.h"
#include "Impl/OpenGL/OpenGLShader.h"


namespace Bubatsu
{
    SRef<Shader> Shader::Create(const String& filepath)
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None:BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return std::make_shared<OpenGLShader>(filepath);
        }

        BBZ_CORE_ASSERT(true, "VertexArray::Unknown RenderApi!");
        return nullptr;
    }
    SRef<Shader> Shader::Create(const String& name, const String& vertexSrc, const String& fragmentSrc)
    {
        switch (Renderer::GetApi())
        {
        case RenderApi::Api::None: BBZ_CORE_ASSERT(true, "RenderApi::None Is Currently Not Supported!"); return nullptr;
        case RenderApi::Api::OpenGL: return std::make_shared <OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        BBZ_CORE_ASSERT(true, "VertexArray::Unknown RenderApi!");
        return nullptr;
    }

    void ShaderLibrary::Add(const SRef<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    void ShaderLibrary::Add(const String& name, const SRef<Shader>& shader)
    {
        BBZ_CORE_ASSERT(Exists(name), "Shader Already Exsists");
        m_Shaders[name] = shader;
    }

    SRef<Shader> ShaderLibrary::Load(const String& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    SRef<Shader> ShaderLibrary::Load(const String& name, const String& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    SRef<Shader> ShaderLibrary::Get(const String& name)
    {
        BBZ_CORE_ASSERT(!Exists(name), "Shader Not Found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const String& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}

