#include "ExampleRenderer2D.h"
#include "imgui.h"

ExampleRenderer2D::ExampleRenderer2D()
    : Layer("ExampleRenderer2D"), m_Camera(690.0f / 420.0f) {}

void ExampleRenderer2D::OnAttach()
{
    m_Texture = Bubatsu::Texture2D::Create("assets/textures/chicken.png");
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

    Bubatsu::Renderer2D::DrawQuad({  0.0f,  0.0f },  0.0f, { 0.8f, 0.8f }, m_Color);
    Bubatsu::Renderer2D::DrawQuad({ -1.1f,  0.1f }, 45.0f, { 1.2f, 1.2f }, m_Color);
    Bubatsu::Renderer2D::DrawQuad({  0.0f,  1.5f, -0.1f },  0.0f, { 9.9f, 9.9f }, m_Texture);

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
