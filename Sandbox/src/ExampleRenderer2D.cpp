#include "ExampleRenderer2D.h"
#include "imgui.h"


ExampleRenderer2D::ExampleRenderer2D()
    : Layer("ExampleRenderer2D"), m_Camera(690.0f / 420.0f) {}

void ExampleRenderer2D::OnAttach()
{
    m_SpriteSheet = Bubatsu::Texture2D::Create("Assets/Textures/SpriteSheet.png");
    m_TextureStairs = Bubatsu::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7.0f, 6.0f }, { 64.0f, 64.0f });
    m_TextureTree = Bubatsu::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 4.0f, 1.0f }, { 64.0f, 64.0f }, { 1.0f, 2.0f });

    Bubatsu::RenderCommand::SetClearColor(Bubatsu::FVec4(0.125f, 0.1f, 0.15f, 1.0f));
}

void ExampleRenderer2D::OnDetach()
{
}

void ExampleRenderer2D::OnUpdate(Bubatsu::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    Bubatsu::RenderCommand::Clear();
    Bubatsu::Renderer2D::BeginScene(m_Camera.GetCamera());

    Bubatsu::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureStairs);
    Bubatsu::Renderer2D::DrawQuad({ 2.0f, 0.0f }, { 1.0f, 2.0f }, m_TextureTree, { 0.8f, 0.8f, 1.0f, 1.0f });

    Bubatsu::Renderer2D::EndScene();
}

void ExampleRenderer2D::OnImGuiRender()
{
    ImGui::Begin("Statistics");

    auto statistics = Bubatsu::Renderer2D::GetStatistics();

    ImGui::Text("Render Calls:\t%d", statistics.DrawCalls);
    ImGui::Text("QuadCount:   \t%d", statistics.QuadCount);
    ImGui::Text("VertexCount: \t%d", statistics.GetVertexCount());
    ImGui::Text("IndexCount:  \t%d", statistics.GetIndexCount());

    ImGui::End();
}

void ExampleRenderer2D::OnEvent(Bubatsu::Event& e)
{
    m_Camera.OnEvent(e);
}

