#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Lynton/Renderer/Shader.h"

namespace Lynton
{

	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_renderer_id;
	public:
		OpenGLShader(const std::string& vertex_src, const std::string& fragment_src);
		virtual ~OpenGLShader();

		void bind() const override;
		void unbind() const override;

		void upload_uniform_int(const std::string& name, const int value);
		void upload_uniform_float(const std::string& name, const float value);
		void upload_uniform_vec2(const std::string& name, const glm::vec2& vector);
		void upload_uniform_vec3(const std::string& name, const glm::vec3& vector);
		void upload_uniform_vec4(const std::string& name, const glm::vec4& vector);
		void upload_uniform_mat3(const std::string& name, const glm::mat3& matrix);
		void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix);
	};

}

