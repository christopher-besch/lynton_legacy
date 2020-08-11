#pragma once

#include "Lynton/Core/Layer.h"
#include "Lynton/Events/ApplicationEvent.h"
#include "Lynton/Events/KeyEvent.h"
#include "Lynton/Events/MouseEvent.h"

namespace Lynton
{

	// engine defined ImGui overlay
	class  ImGuiLayer : public Layer
	{
	private:
		float m_time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void on_attach() override;
		virtual void on_detach() override;
		virtual void on_imgui_render() override;

		void begin();
		void end();
	};

}
