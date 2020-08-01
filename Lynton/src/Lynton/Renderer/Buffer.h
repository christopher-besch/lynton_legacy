/*
 * a bunch of interfaces for abstracting different rendering apis
 */
#pragma once

#include <cstdint>

namespace Lynton
{

	// used in the vertex buffer
	enum class ShaderDataType
	{
	    none = 0,
		float1,
		float2,
		float3,
		float4,
		mat3,
		mat4,
		int1,
		int2,
		int3,
		int4,
		bool1
	};

	static uint32_t shader_data_type_size(ShaderDataType type)
	{
	    switch (type)
	    {
		case ShaderDataType::float1: return sizeof(float) * 1;
		case ShaderDataType::float2: return sizeof(float) * 2;
		case ShaderDataType::float3: return sizeof(float) * 3;
		case ShaderDataType::float4: return sizeof(float) * 4;
		case ShaderDataType::mat3:   return sizeof(float) * 3 * 3;
		case ShaderDataType::mat4:   return sizeof(float) * 4 * 4;
		case ShaderDataType::int1:   return sizeof(int)   * 1;
		case ShaderDataType::int2:   return sizeof(int)   * 2;
		case ShaderDataType::int3:   return sizeof(int)   * 3;
		case ShaderDataType::int4:   return sizeof(int)   * 4;
		case ShaderDataType::bool1:  return sizeof(bool)  * 1;
		default:
			LY_CORE_ASSERT(false, "Unknown ShaderDataType!")
			return 0;
	    }
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		    : name(name), type(type), size(shader_data_type_size(type)), offset(0), normalized(normalized) {}

		uint32_t get_component_count() const
		{
		    switch (type)
		    {
			case ShaderDataType::float1: return 1;
			case ShaderDataType::float2: return 2;
			case ShaderDataType::float3: return 3;
			case ShaderDataType::float4: return 4;
			case ShaderDataType::mat3:   return 3 * 3;
			case ShaderDataType::mat4:   return 4 * 4;
			case ShaderDataType::int1:   return 1;
			case ShaderDataType::int2:   return 2;
			case ShaderDataType::int3:   return 3;
			case ShaderDataType::int4:   return 4;
			case ShaderDataType::bool1:  return 1;
			default:
				LY_CORE_ASSERT(false, "Unknwon ShaderDataType!")
				return 0;
		    }
		}
	};


	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	private:
		void calculate_offset_and_stride()
		{
			// pointer to the beginning of the attribute inside each vertex
			uint32_t offset = 0;
			// size of each vertex
			m_stride = 0;
		    for (auto& element : m_elements)
		    {
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
		    }
		}
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
		    : m_elements(elements)
		{
			calculate_offset_and_stride();
		}

		inline const std::vector<BufferElement>& get_elements() const { return m_elements; }
		inline uint32_t get_stride() const { return m_stride; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
	};


	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_layout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& get_layout() const = 0;

		static VertexBuffer* create(uint32_t size, float* vertices);
	};

	class IndexBuffer
	{
	public:
	    virtual ~IndexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t get_count() const = 0;

		static IndexBuffer* create(uint32_t count, uint32_t* indices);
	};

}
