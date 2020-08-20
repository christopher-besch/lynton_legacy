#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Lynton/Renderer/Shader.h"

// ToDo: remove
typedef unsigned int GLenum;

namespace Lynton
{

	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_renderer_id;
		std::string m_name;
	private:
		void compile(const std::unordered_map<GLenum, std::string>& shader_sources);
		std::string read_file(const std::string& filepath);
		std::unordered_map<GLenum, std::string> pre_process(const std::string& source);
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void set_mat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void set_vec3(const std::string& name, const glm::vec3& vector) override;
		virtual void set_vec4(const std::string& name, const glm::vec4& vector) override;
		virtual void set_float(const std::string& name, const float value) override;
		virtual void set_int(const std::string& name, const int value) override;
		virtual void set_int_array(const std::string& name, const int* values, uint32_t count) override;

		inline virtual const std::string& get_name() const override { return m_name; }

		void upload_uniform_int(const std::string& name, const int value);
		void upload_uniform_float(const std::string& name, const float value);
		void upload_uniform_vec2(const std::string& name, const glm::vec2& vector);
		void upload_uniform_vec3(const std::string& name, const glm::vec3& vector);
		void upload_uniform_vec4(const std::string& name, const glm::vec4& vector);
		void upload_uniform_mat3(const std::string& name, const glm::mat3& matrix);
		void upload_uniform_mat4(const std::string& name, const glm::mat4& matrix);
		void upload_uniform_int_array(const std::string& name, const int* values, uint32_t count);
	};

}

