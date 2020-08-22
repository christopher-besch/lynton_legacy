#pragma once

#include "glad/glad.h"
#include "Lynton/Renderer/Texture.h"

namespace Lynton
{

	class OpenGLTexture2D : public Texture2D
	{
	private:
		std::string m_path;
		uint32_t m_width, m_height;
		uint32_t m_renderer_id;
		GLenum m_internal_format = 0, m_data_format = 0;
		size_t m_bytes_per_pixel;
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t get_width() const override { return m_width; }
		virtual uint32_t get_height() const override { return m_height; }
		virtual uint32_t get_renderer_id() const override { return m_renderer_id; }

		virtual void set_data(void* data, size_t size) override;

		virtual void bind(uint32_t slot = 0) const;

		virtual bool operator==(const Texture& other) override
		{
			return m_renderer_id == ((OpenGLTexture2D&)other).m_renderer_id;
		}
	};

}
