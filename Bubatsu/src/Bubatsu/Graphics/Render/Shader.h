#pragma once

#include "Bubatsu/Core/Core.h"


namespace Bubatsu
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const String& GetName() const = 0;

		static SPtr<Shader> Create(const String& filepath);
		static SPtr<Shader> Create(const String& name, const String& vertexSrc, const String& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const SPtr<Shader>& shader);
		void Add(const String& name, const SPtr<Shader>& shader);
		SPtr<Shader> Load(const String& filepath);
		SPtr<Shader> Load(const String& name, const String& filepath);

		SPtr<Shader> Get(const String& name);

		bool Exists(const String& name) const;
	private:
		std::unordered_map<String, SPtr<Shader>> m_Shaders;
	};
}