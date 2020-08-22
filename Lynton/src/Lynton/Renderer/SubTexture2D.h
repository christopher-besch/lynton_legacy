#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

namespace Lynton
{

	class SubTexture2D
	{
	private:
		Ref<Texture2D> m_texture;

		glm::vec2 m_tex_coords[4];
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D> get_texture() const { return m_texture; }
		const glm::vec2* get_tex_coords() const { return m_tex_coords; }

		static Ref<SubTexture2D> create_from_coords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cell_size, const glm::vec2& sprite_size = { 1, 1 });
	};

}
