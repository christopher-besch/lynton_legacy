#pragma once

#include "Core/TimeStep.h"
#include "Lynton/Core.h"
#include "Lynton/Events/Event.h"

namespace Lynton
{

	class Layer
	{
	protected:
		std::string m_debug_name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update(TimeStep time_step) {}
		virtual void on_event(Event& event) {}
		virtual void on_imgui_render() {}

		inline const std::string& get_name() const { return m_debug_name; }
	};

}
