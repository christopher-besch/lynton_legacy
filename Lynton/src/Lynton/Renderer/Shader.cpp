#include "lypch.h"
#include "Shader.h"

#include "Lynton/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Lynton
{
    // create Shader instances for the currently used rendering api
    Ref<Shader> Shader::create(const std::string& filepath)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLShader>(filepath);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
    }
    
    Ref<Shader> Shader::create(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
    {
        switch (Renderer::get_api())
        {
        case RendererAPI::API::none:
            LY_CORE_ASSERT(false, "RendererAPI::none is not supported!")
            return nullptr;
        case RendererAPI::API::open_gl:
            return create_ref<OpenGLShader>(name, vertex_src, fragment_src);
        default:
            LY_CORE_ASSERT(false, "The requested RendererAPI is not supported!")
            return nullptr;
        }
    }

    void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
    {
        LY_CORE_ASSERT(!exists(name), "Shader already exists!")
        m_shaders[name] = shader;
    }

    void ShaderLibrary::add(const Ref<Shader>& shader)
    {
        auto& name = shader->get_name();
        add(name, shader);
    }

    Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string& filepath)
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string& name)
    {
        LY_CORE_ASSERT(exists(name), "Shader not found!")
        return m_shaders[name];
    }
    bool ShaderLibrary::exists(const std::string& name) const
    {
        return m_shaders.find(name) != m_shaders.end();
    }
}
