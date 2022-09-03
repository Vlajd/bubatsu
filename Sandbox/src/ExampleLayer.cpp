#include "ExampleLayer.h"
#include "Impl/OpenGL/OpenGLShader.h"

ExampleLayer::ExampleLayer()
    : Layer("Example"), m_Camera(690.0f / 420.0f, false), m_SquarePosition(0.0f)
{
    m_VertexArray = Bubatsu::VertexArray::Create();

    float vertices[3 * 7] =
    {
        -0.5f, -0.5f, 0.0f, 0.1f, 0.15f, 0.2f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.1f, 0.1f, 0.7f, 0.25f,
         0.5f, -0.5f, 0.0f, 0.15f, 0.1f, 0.2f, 0.0f
    };

    Bubatsu::SRef<Bubatsu::VertexBuffer> vertexBuffer;
    vertexBuffer = Bubatsu::VertexBuffer::Create(vertices, sizeof(vertices));

    Bubatsu::BufferLayout layout =
    {
        { Bubatsu::DataType::FVec3, "a_Position" },
        { Bubatsu::DataType::FVec4, "a_Color" }
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };

    Bubatsu::SRef<Bubatsu::IndexBuffer> indexBuffer;
    indexBuffer = Bubatsu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA = Bubatsu::VertexArray::Create();

    float squareVertices[5 * 4] =
    {
        -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f, 0.0f, 1.0f
    };

    Bubatsu::SRef<Bubatsu::VertexBuffer> squareVB;
    squareVB = Bubatsu::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

    squareVB->SetLayout(
    {
        { Bubatsu::DataType::FVec3, "a_Position" },
        { Bubatsu::DataType::FVec2, "a_TexCoord"}
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Bubatsu::SRef<Bubatsu::IndexBuffer> squareIB;
    squareIB = Bubatsu::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    // [[Shader1]]
    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;	

        void main() {
            //color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
            color = v_Color;
        }
    )";

    m_Shader = Bubatsu::Shader::Create("VertexColorTriangle", vertexSrc, fragmentSrc);

    // [[Shader2]]

    std::string flatColorShaderVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;

        void main() {

            v_Position = a_Position;
            gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
        }
    )";

    std::string flatColorShaderFragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        uniform vec3 u_Color;

        void main() {

            color = vec4(u_Color, 1.0f);
        }
    )";

    m_FlatColorShader = Bubatsu::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

    // [[Shader2]]


    // [[Shader3]]
    auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

    m_Texture = (Bubatsu::Texture2D::Create("assets/textures/Checkerboard.png"));
    m_CodeChickenTexture = (Bubatsu::Texture2D::Create("assets/textures/chicken.png"));

    std::dynamic_pointer_cast<Bubatsu::OpenGLShader>(textureShader)->Bind();
    std::dynamic_pointer_cast<Bubatsu::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    // [[Shader3]]
}

void ExampleLayer::OnUpdate(Bubatsu::Timestep ts)
{
    m_Camera.OnUpdate(ts);

    Bubatsu::RenderCommand::SetClearColor(Bubatsu::FVec4(0.14f, 0.15f, 0.16f, 1.0f));
    Bubatsu::RenderCommand::Clear();

    // Begin Scene
    Bubatsu::Renderer::BeginScene(m_Camera.GetCamera());

    static Bubatsu::FMat4 scale = Bubatsu::Scale(Bubatsu::FMat4(1.0f), Bubatsu::FVec3(0.1f));

    std::dynamic_pointer_cast<Bubatsu::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Bubatsu::OpenGLShader>(m_FlatColorShader)->UploadUniformFVec3("u_Color", m_SquareColor);

    for (int x = 0; x < 25; x++)
    {
        for (int y = 0; y < 25; y++)
        {
            Bubatsu::FVec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            Bubatsu::FMat4 transform = Bubatsu::Translate(Bubatsu::FMat4(1.0f), pos) * scale;
            Bubatsu::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
        }
    }

    auto textureShader = m_ShaderLibrary.Get("Texture");

    m_Texture->Bind();
    Bubatsu::Renderer::Submit(textureShader, m_SquareVA, Bubatsu::Scale(Bubatsu::FMat4(1.0f), Bubatsu::FVec3(1.5f)));

    m_CodeChickenTexture->Bind();
    Bubatsu::Renderer::Submit(textureShader, m_SquareVA, Bubatsu::Scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // Triangle
    //Bubatsu::Renderer::Submit(m_Shader, m_VertexArray);

    Bubatsu::Renderer::EndScene();
    // End Scene
}

void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void ExampleLayer::OnEvent(Bubatsu::Event& e)
{
    m_Camera.OnEvent(e);
}


