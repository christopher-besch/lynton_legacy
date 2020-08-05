#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Lynton
{

	// handle shaders
	class Shader
	{
	private:
		uint32_t m_renderer_id;
	public:
		Shader(const std::string& vertex_src, const std::string& fragment_src);
		~Shader();

		void bind() const;
		void unbind() const;

		void upload_uniform_vec4(const std::string& name, const glm::vec4& vector);
		void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix);
	};

}

