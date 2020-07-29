#include "lypch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace Lynton
{
    Shader::Shader(const std::string& vertex_src, const std::string& fragment_src)
    {
		// create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// send the vertex shader source code to OpenGL
		// note that std::string's .c_str is NULL character terminated.
		const char* source = vertex_src.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// compile the vertex shader
		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// the maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// we don't need the shader anymore.
			glDeleteShader(vertexShader);

			LY_CORE_ERROR("{0}", infoLog.data());
			LY_CORE_ASSERT(false, "Vertex shader compilation failure!")
			return;
		}

		// create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// send the fragment shader source code to GL
		// note that std::string's .c_str is NULL character terminated.
		source = fragment_src.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// the maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// we don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			LY_CORE_ERROR("{0}", infoLog.data());
			LY_CORE_ASSERT(false, "Fragment shader compilation failure!")
			return;
		}

		// vertex and fragment shaders are successfully compiled.
		// now time to link them together into a program.
		// get a program object.
		m_renderer_id = glCreateProgram();

		// attach our shaders to our program
		glAttachShader(m_renderer_id, vertexShader);
		glAttachShader(m_renderer_id, fragmentShader);

		// link our program
		glLinkProgram(m_renderer_id);

		// note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_renderer_id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &maxLength);

			// the maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_renderer_id, maxLength, &maxLength, &infoLog[0]);

			// we don't need the program anymore.
			glDeleteProgram(m_renderer_id);
			// don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LY_CORE_ERROR("{0}", infoLog.data());
			LY_CORE_ASSERT(false, "Shader link failure!")
			return;
		}

		// always detach shaders after a successful link.
		glDetachShader(m_renderer_id, vertexShader);
		glDetachShader(m_renderer_id, fragmentShader);
    }

    Shader::~Shader()
    {
    }

    void Shader::bind() const
    {
		glUseProgram(m_renderer_id);
    }

    void Shader::unbind() const
    {
		glUseProgram(0);
    }
}
