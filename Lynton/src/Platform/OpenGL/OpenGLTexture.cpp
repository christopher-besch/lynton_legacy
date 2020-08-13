#include "lypch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Lynton
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	    : m_path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LY_CORE_ASSERT(data, "Failed to load image ({0})!", path)
		m_width = width;
		m_height = height;

		GLenum internal_format = 0, data_format = 0;
		switch (channels)
		{
		case 4:
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
			break;
		case 3:
			internal_format = GL_RGB8;
			data_format = GL_RGB;
			break;
		default:
			LY_CORE_ASSERT(false, "The Texture loader doesn't support images with {0} channels!", channels);
		}
		
		LY_CORE_ASSERT(internal_format & data_format, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
		glTextureStorage2D(m_renderer_id, 1, internal_format, m_width, m_height);

		glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_renderer_id);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_renderer_id);
	}

}
