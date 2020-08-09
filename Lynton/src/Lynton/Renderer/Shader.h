#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Lynton
{

	// interface for handling shader
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& get_name() const = 0;

		static Ref<Shader> create(const std::string& filepath);
		static Ref<Shader> create(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
	};


	class ShaderLibrary
	{
	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	public:
		void add(const std::string& name, const Ref<Shader>& shader);
		void add(const Ref<Shader>& shader);
		Ref<Shader> load(const std::string& name, const std::string& filepath);
		Ref<Shader> load(const std::string& filepath);

		Ref<Shader> get(const std::string& name);
		bool exists(const std::string& name) const;
	};

}

