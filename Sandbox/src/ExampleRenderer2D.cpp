#include "ExampleRenderer2D.h"
#include "imgui.h"

ExampleRenderer2D::ExampleRenderer2D()
    : Layer("ExampleRenderer2D"), m_Camera(690.0f / 420.0f) {}

void ExampleRenderer2D::OnAttach()
{
    m_Texture = Bubatsu::Texture2D::Create("Assets/Textures/Checkerboard.png");
    Bubatsu::RenderCommand::SetClearColor(Bubatsu::FVec4(0.1f, 0.1f, 0.1f, 1.0f));
}

void ExampleRenderer2D::OnDetach()
{
}

void ExampleRenderer2D::OnUpdate(Bubatsu::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    Bubatsu::RenderCommand::Clear();

    Bubatsu::Renderer2D::BeginScene(m_Camera.GetCamera());

    for (float y = -5.0f; y < 5.0f; y += 0.5f)
    {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
            Bubatsu::FVec4 color = { (x + 5.0f) / 10.0f, 0.2f, (y + 5.0f) / 10.0f, 1.0f };
            Bubatsu::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
        }
    }

    Bubatsu::Renderer2D::EndScene();
}

void ExampleRenderer2D::OnImGuiRender()
{
    ImGui::Begin("Statistics");

    auto statistics = Bubatsu::Renderer2D::GetStatistics();

    ImGui::Text("Render Calls:\t%d", statistics.DrawCalls);
    ImGui::Text("QuadCount:\t%d", statistics.QuadCount);
    ImGui::Text("VertexCount:\t%d", statistics.GetVertexCount());
    ImGui::Text("IndexCOunt:\t%d", statistics.GetIndexCount());

    ImGui::End();
}

void ExampleRenderer2D::OnEvent(Bubatsu::Event& e)
{
    m_Camera.OnEvent(e);
}

