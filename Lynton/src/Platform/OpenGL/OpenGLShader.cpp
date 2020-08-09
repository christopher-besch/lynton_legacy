#include "lypch.h"
// ToDo: remove
#include "OpenGLShader.h"

#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace Lynton
{

	static GLenum shader_type_from_string(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		LY_CORE_ASSERT(false, "unsupported shader type!", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = read_file(filepath);

		auto shader_sources = pre_process(source);
		compile(shader_sources);

		// extract name from file path
		auto behind_last_slash = filepath.find_last_of("/\\");
		behind_last_slash = behind_last_slash == std::string::npos ? 0 : behind_last_slash + 1;
		auto last_dot = filepath.rfind(".");
		auto count = last_dot == std::string::npos ? filepath.size() - behind_last_slash : last_dot - behind_last_slash;
		m_name = filepath.substr(behind_last_slash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
	    : m_name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex_src;
		sources[GL_FRAGMENT_SHADER] = fragment_src;
		compile(sources);
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shader_sources)
	{
		GLuint program = glCreateProgram();
		LY_CORE_ASSERT(shader_sources.size() <= 16, "Only up to 16 shaders are supported!")
		std::array<GLenum, 8> gl_shader_ids;
		int gl_shader_id_index = 0;
		for (auto& kv : shader_sources)
		{
			GLenum type = kv.first;
			const std::string source = kv.second;
			const char* source_c_str = source.c_str();

			GLuint shader = glCreateShader(type);

			glShaderSource(shader, 1, &source_c_str, 0);
			glCompileShader(shader);

			int is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
			if (is_compiled == GL_FALSE)
			{
				int max_length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

				std::vector<GLchar> infoLog(max_length);
				glGetShaderInfoLog(shader, max_length, &max_length, &infoLog[0]);

				glDeleteShader(shader);

				LY_CORE_ERROR("{0}", infoLog.data());
				LY_CORE_ASSERT(false, "Shader compilation failure!");
				return;
			}
			glAttachShader(program, shader);
			gl_shader_ids[gl_shader_id_index++] = (shader);
		}

        glLinkProgram(program);

		GLint is_linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> info_log(max_length);
			glGetProgramInfoLog(program, max_length, &max_length, &info_log[0]);

			glDeleteProgram(program);
			for (auto id : gl_shader_ids)
			    glDeleteShader(id);

			LY_CORE_ERROR("{0}", info_log.data());
			LY_CORE_ASSERT(false, "Shader link failure!")
			return;
		}

		for (auto id : gl_shader_ids)
			glDetachShader(program, id);
		m_renderer_id = program;
	}

	std::string OpenGLShader::read_file(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
			LY_CORE_ERROR("COuld not open file '{0}'!", filepath);
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::pre_process(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shader_sources;
		
		const char* type_token = "#type";
		size_t type_token_length = strlen(type_token);
		size_t pos = source.find(type_token, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			LY_CORE_ASSERT(eol != std::string::npos, "Syntax error while shader loading!");
			size_t begin = pos + type_token_length + 1;
			std::string type = source.substr(begin, eol - begin);
			LY_CORE_ASSERT(shader_type_from_string(type), "Invalid shader type specified!");
		
			size_t next_line_pos = source.find_first_not_of("\r\n", eol);
			pos = source.find(type_token, next_line_pos);
			shader_sources[shader_type_from_string(type)] =
				source.substr(next_line_pos,
					pos - (next_line_pos == std::string::npos ? source.size() - 1 : next_line_pos));
		}
		return shader_sources;
	}

	OpenGLShader::~OpenGLShader()
	{
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_renderer_id);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

    void OpenGLShader::upload_uniform_int(const std::string& name, const int value)
    {
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform1i(location, value);
    }

    void OpenGLShader::upload_uniform_float(const std::string& name, const float value)
    {
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform1f(location, value);
    }

    void OpenGLShader::upload_uniform_vec2(const std::string& name, const glm::vec2& vector)
    {
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform2f(location, vector.x, vector.y);
    }

    void OpenGLShader::upload_uniform_vec3(const std::string& name, const glm::vec3& vector)
    {
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::upload_uniform_vec4(const std::string& name, const glm::vec4& vector)
	{
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::upload_uniform_mat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::upload_uniform_mat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_renderer_id, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
