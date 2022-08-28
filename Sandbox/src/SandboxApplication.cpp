#include "Bubatsu.h"

#include "Impl/OpenGL/OpenGLShader.h"

#include <imgui.h>

class ExampleLayer : public Bubatsu::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{

		m_VertexArray.reset(Bubatsu::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.1f, 0.15f, 0.2f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.1f, 0.1f, 0.7f, 0.25f,
			 0.5f, -0.5f, 0.0f, 0.15f, 0.1f, 0.2f, 0.0f
		};

		Bubatsu::SPtr<Bubatsu::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Bubatsu::VertexBuffer::Create(vertices, sizeof(vertices)));

		Bubatsu::BufferLayout layout =
		{
			{ Bubatsu::DataType::FVec3, "a_Position" },
			{ Bubatsu::DataType::FVec4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		Bubatsu::SPtr<Bubatsu::IndexBuffer> indexBuffer;
		indexBuffer.reset(Bubatsu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Bubatsu::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};

		Bubatsu::SPtr<Bubatsu::VertexBuffer> squareVB;
		squareVB.reset(Bubatsu::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout(
		{
			{ Bubatsu::DataType::FVec3, "a_Position" },
			{ Bubatsu::DataType::FVec2, "a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Bubatsu::SPtr<Bubatsu::IndexBuffer> squareIB;
		squareIB.reset(Bubatsu::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

	virtual void OnUpdate(Bubatsu::Timestep ts) override {

		if (Bubatsu::Input::IsKeyboardPressed(BBZ_KEY_A)) m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (Bubatsu::Input::IsKeyboardPressed(BBZ_KEY_D)) m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Bubatsu::Input::IsKeyboardPressed(BBZ_KEY_S)) m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		if (Bubatsu::Input::IsKeyboardPressed(BBZ_KEY_W)) m_CameraPosition.y += m_CameraMoveSpeed * ts;
		if (Bubatsu::Input::IsKeyboardPressed(BBZ_KEY_E)) m_CameraRotation -= m_CameraRotationSpeed * ts;
		if (Bubatsu::Input::IsKeyboardPressed(BBZ_KEY_Q)) m_CameraRotation += m_CameraRotationSpeed * ts;

		Bubatsu::RenderCommand::SetClearColor(Bubatsu::FVec4(0.14f, 0.15f, 0.16f, 1.0f));
		Bubatsu::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		// Begin Scene
		Bubatsu::Renderer::BeginScene(m_Camera);

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

	virtual void OnImGuiRender() override
	{
		// ImGui Code Here
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Bubatsu::Event& event) override
	{
		// OnEvent Actions Here
	}

private:

	Bubatsu::ShaderLibrary m_ShaderLibrary;

	Bubatsu::SPtr<Bubatsu::Shader> m_Shader;
	Bubatsu::SPtr<Bubatsu::VertexArray> m_VertexArray;

	Bubatsu::SPtr<Bubatsu::Shader> m_FlatColorShader;
	Bubatsu::SPtr<Bubatsu::VertexArray> m_SquareVA;

	// texture
	Bubatsu::SPtr<Bubatsu::Texture2D> m_Texture, m_CodeChickenTexture;

	Bubatsu::OrthographicCamera m_Camera;

	Bubatsu::FVec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 190.0f;

	Bubatsu::FVec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

	Bubatsu::FVec3 m_SquareColor = Bubatsu::FVec3(0.2f, 0.3f, 0.8f);
};

class Sandbox : public Bubatsu::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

namespace Bubatsu
{
	Application* CreateApplication()
	{
		return new Sandbox();
	}
}

