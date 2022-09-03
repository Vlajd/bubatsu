#pragma once

#include "Bubatsu.h"

class ExampleRenderer2D : public Bubatsu::Layer
{
public:
    ExampleRenderer2D();
    virtual ~ExampleRenderer2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(Bubatsu::Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Bubatsu::Event& e) override;

private:
    Bubatsu::OrthographicCameraController m_Camera;
    Bubatsu::SRef<Bubatsu::VertexArray> m_VA;
    Bubatsu::SRef<Bubatsu::Shader> m_Shader;
    Bubatsu::SRef<Bubatsu::Texture2D> m_Texture;
    Bubatsu::FVec4 m_Color = Bubatsu::FVec4(0.1f, 0.5f, 0.7f, 1.0f);
};

