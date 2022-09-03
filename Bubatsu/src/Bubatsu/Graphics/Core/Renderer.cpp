#include "bbzpch.h"
#include "Renderer.h"

#include "Bubatsu/Graphics/Renderer/Renderer2D.h"

#include "Impl/OpenGL/OpenGLShader.h"


namespace Bubatsu
{
    SRef<Renderer::SceneData> Renderer::s_SceneData = NewSRef<Renderer::SceneData>();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResized(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
        // Optional TODO
    }

    void Renderer::Submit(const SRef<Shader>& shader, const SRef<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        shader->SetFMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetFMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}