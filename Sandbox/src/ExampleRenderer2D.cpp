#include "ExampleRenderer2D.h"
#include "imgui.h"

ExampleRenderer2D::ExampleRenderer2D()
    : Layer("ExampleRenderer2D"), m_Camera(690.0f / 420.0f) {}

void ExampleRenderer2D::OnAttach()
{
    m_Texture = Bubatsu::Texture2D::Create("Assets/Textures/chicken.png");
}

void ExampleRenderer2D::OnDetach()
{
}

void ExampleRenderer2D::OnUpdate(Bubatsu::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    Bubatsu::RenderCommand::SetClearColor(Bubatsu::FVec4(0.1f, 0.1f, 0.1f, 1.0f));
    Bubatsu::RenderCommand::Clear();

    Bubatsu::Renderer2D::BeginScene(m_Camera.GetCamera());

    Bubatsu::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.8f, 0.8f }, m_Color);
    Bubatsu::Renderer2D::DrawQuad({ 5.0f, 5.0f }, { 1.8f, 0.8f }, m_Color);
    Bubatsu::Renderer2D::DrawQuad({ -5.0f, -5.0f }, { 1.8f, 0.8f }, m_Color);
    Bubatsu::Renderer2D::DrawQuad({ 10.0f, 10.0f }, 125.0f, { 3.0f, 3.0f }, m_Texture, { 0.0f, 0.2f, 0.5f, 1.0f });
    Bubatsu::Renderer2D::DrawQuad({ 5.0f, 10.0f }, { 3.0f, 3.0f }, m_Texture, 2.0f);

    Bubatsu::Renderer2D::EndScene();
}

void ExampleRenderer2D::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", RawValuePtr(m_Color));

    ImGui::End();
}

void ExampleRenderer2D::OnEvent(Bubatsu::Event& e)
{
    m_Camera.OnEvent(e);
}
