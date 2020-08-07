#pragma once
#include <cstdint>
#include <string>

#include "Lynton/Core.h"

namespace Lynton
{
	// interface for all sorts of textures
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t get_width() const = 0;
		virtual uint32_t get_height() const = 0;

		virtual void bind(uint32_t slot = 0) const = 0;
	};


	// interface
	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> create(const std::string& path);
	};

}
