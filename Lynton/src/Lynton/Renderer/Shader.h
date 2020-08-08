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

		static Shader* create(const std::string& filepath);
		static Shader* create(const std::string& vertex_src, const std::string& fragment_src);
	};

}

