#include "bbzpch.h"
#include "Renderer2D.h"

#include "Bubatsu/Graphics/Core/RenderCommand.h"


namespace Bubatsu
{
    URef<Renderer2D::Renderer2DData> Renderer2D::s_Data;

    void Renderer2D::Init()
    {
        s_Data = NewURef<Renderer2DData>();
        s_Data->QuadVA = VertexArray::Create();

        float quadVertices[5 * 4] =
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        SRef<VertexBuffer> quadVB;
        quadVB = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
        quadVB->SetLayout({
            { DataType::FVec3, "a_Position" },
            { DataType::FVec2, "a_TexCoord" }
        });
        s_Data->QuadVA->AddVertexBuffer(quadVB);

        uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
        SRef<IndexBuffer> quadIB;
        quadIB = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
        s_Data->QuadVA->SetIndexBuffer(quadIB);

        s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
        s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data.get();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetFMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetFMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, color);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color)
    {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetFVec4("u_Color", color);

        FMat4 transform = Translate(FMat4(1.0f), position) *
                          Rotate(FMat4(1.0f), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)) *
                          Scale(FMat4(1.0f), FVec3(size, 1.0f));
        s_Data->FlatColorShader->SetFMat4("u_Transform", transform);

        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA);
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture)
    {
        s_Data->TextureShader->Bind();

        FMat4 transform = Translate(FMat4(1.0f), position) *
            Rotate(FMat4(1.0f), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)) *
            Scale(FMat4(1.0f), FVec3(size, 1.0f));
        s_Data->TextureShader->SetFMat4("u_Transform", transform);

        texture->Bind();

        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA);
    }
}

