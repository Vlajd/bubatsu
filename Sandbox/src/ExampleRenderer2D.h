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
    Bubatsu::SRef<Bubatsu::Texture2D> m_SpriteSheet;
    Bubatsu::SRef<Bubatsu::SubTexture2D> m_TextureStairs;
    Bubatsu::SRef<Bubatsu::SubTexture2D> m_TextureTree;
};

