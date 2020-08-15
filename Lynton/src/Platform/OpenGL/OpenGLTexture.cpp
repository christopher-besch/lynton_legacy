#include "lypch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Lynton
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
		LY_PROFILE_FUNCTION();

		m_internal_format = GL_RGBA8;
		m_data_format = GL_RGBA;
		m_bytes_per_pixel = 4;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
		glTextureStorage2D(m_renderer_id, 1, m_internal_format, m_width, m_height);

		glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }


	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	    : m_path(path)
	{
		LY_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		{
			LY_PROFILE_SCOPE("stbi_load in OpenGLTexture2D::OpenGLTexture2D(const std::string&)");

		    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		LY_CORE_ASSERT(data, "Failed to load image ({0})!", path)
		m_width = width;
		m_height = height;

		switch (channels)
		{
		case 4:
			m_internal_format = GL_RGBA8;
			m_data_format = GL_RGBA;
			m_bytes_per_pixel = 4;
			break;
		case 3:
			m_internal_format = GL_RGB8;
			m_data_format = GL_RGB;
			m_bytes_per_pixel = 3;
			break;
		default:
			LY_CORE_ASSERT(false, "The Texture loader doesn't support images with {0} channels!", channels);
		}
		
		LY_CORE_ASSERT(m_internal_format & m_data_format, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
		glTextureStorage2D(m_renderer_id, 1, m_internal_format, m_width, m_height);

		glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		LY_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_renderer_id);
	}

    void OpenGLTexture2D::set_data(void* data, size_t size)
    {
		LY_PROFILE_FUNCTION();

		LY_CORE_ASSERT(size == m_width * m_height * m_bytes_per_pixel, "Data must be entire texture!");
		glTextureSubImage2D(m_renderer_id, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, data);
    }

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		LY_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_renderer_id);
	}

}
