#pragma once

#include <Bubatsu.h>
#include <imgui.h>

class ExampleLayer : public Bubatsu::Layer
{
public:
    ExampleLayer();


    virtual void OnUpdate(Bubatsu::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Bubatsu::Event& e) override;
    
private:

    Bubatsu::ShaderLibrary m_ShaderLibrary;

    Bubatsu::SRef<Bubatsu::Shader> m_Shader;
    Bubatsu::SRef<Bubatsu::VertexArray> m_VertexArray;

    Bubatsu::SRef<Bubatsu::Shader> m_FlatColorShader;
    Bubatsu::SRef<Bubatsu::VertexArray> m_SquareVA;

    // texture
    Bubatsu::SRef<Bubatsu::Texture2D> m_Texture, m_CodeChickenTexture;

    Bubatsu::OrthographicCameraController m_Camera;

    Bubatsu::FVec3 m_SquarePosition;
    float m_SquareMoveSpeed = 1.0f;

    Bubatsu::FVec3 m_SquareColor = Bubatsu::FVec3(0.2f, 0.3f, 0.8f);
};
