#include "lypch.h"
#include "SubTexture2D.h"

namespace Lynton
{

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
	    : m_texture(texture)
	{
		m_tex_coords[0] = { min.x, min.y };
		m_tex_coords[1] = { max.x, min.y };
		m_tex_coords[2] = { max.x, max.y };
		m_tex_coords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::create_from_coords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cell_size, const glm::vec2& sprite_size)
	{

		const glm::vec2 min = { (coords.x                   * cell_size.x) / texture->get_width(), (coords.y                   * cell_size.y) / texture->get_height() };
		const glm::vec2 max = { ((coords.x + sprite_size.x) * cell_size.x) / texture->get_width(), ((coords.y + sprite_size.y) * cell_size.y) / texture->get_height() };

	return create_ref<SubTexture2D>(texture, min, max);
	}

}
