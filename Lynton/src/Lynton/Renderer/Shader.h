#pragma once

#include <string>

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

	};

}

