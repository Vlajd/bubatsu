#include "bbzpch.h"
#include "Renderer2D.h"

#include "Bubatsu/Graphics/Core/RenderCommand.h"


namespace Bubatsu
{
    URef<Renderer2D::Renderer2DData> Renderer2D::s_Data;

    void Renderer2D::Init()
    {
        BBZ_PROFILE_FUNCTION();

        // data struct init
        s_Data = NewURef<Renderer2DData>();
        s_Data->QuadVA = VertexArray::Create();

        float quadVertices[5 * 4] =
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        // vertex buffer
        SRef<VertexBuffer> quadVB;
        quadVB = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
        quadVB->SetLayout({
            { DataType::FVec3, "a_Position" },
            { DataType::FVec2, "a_TexCoord" }
        });
        s_Data->QuadVA->AddVertexBuffer(quadVB);

        // index buffer
        uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
        SRef<IndexBuffer> quadIB;
        quadIB = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
        s_Data->QuadVA->SetIndexBuffer(quadIB);

        // empty texture
        s_Data->EmptyTexture = Texture2D::Create(1, 1);
        uint32_t emptyTextureData = 0xffffffff;
        s_Data->EmptyTexture->SetData(&emptyTextureData, sizeof(uint32_t));

        s_Data->Shader = Shader::Create("Assets/Shaders/Texture.glsl");
        s_Data->Shader->Bind();
        s_Data->Shader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        BBZ_PROFILE_FUNCTION();

        delete s_Data.release();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        BBZ_PROFILE_FUNCTION();

        s_Data->Shader->Bind();
        s_Data->Shader->SetFMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
        BBZ_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, FVec4 color)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, color);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, FVec4 color)
    {
        BBZ_PROFILE_FUNCTION();

        s_Data->Shader->SetFVec4("u_Color", color);
        s_Data->EmptyTexture->Bind();

        FMat4 transform = Translate(FMat4(1.0f), position) *
                          Rotate(FMat4(1.0f), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)) *
                          Scale(FMat4(1.0f), FVec3(size, 1.0f));
        s_Data->Shader->SetFMat4("u_Transform", transform);

        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA);
    }

    void Renderer2D::DrawQuad(FVec2 position, float rotation, FVec2 size, const SRef<Texture2D>& texture)
    {
        DrawQuad(FVec3(position, 0.0f), rotation, size, texture);
    }

    void Renderer2D::DrawQuad(FVec3 position, float rotation, FVec2 size, const SRef<Texture2D>& texture)
    {
        BBZ_PROFILE_FUNCTION();

        s_Data->Shader->SetFVec4("u_Color", FVec4(1.0f));

        FMat4 transform = Translate(FMat4(1.0f), position) *
            Rotate(FMat4(1.0f), Radians(rotation), FVec3(0.0f, 0.0f, 1.0f)) *
            Scale(FMat4(1.0f), FVec3(size, 1.0f));
        s_Data->Shader->SetFMat4("u_Transform", transform);

        texture->Bind();

        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA);
    }
}

