#pragma once

#include "Lynton/Layer.h"

namespace Lynton
{

	class LYNTON_API ImGuiLayer : public Layer
	{
	private:
		float m_time = 0;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void on_attach() override;
		void on_dettach() override;

		virtual void on_update() override;
		virtual void on_event(Event& event) override;
	};

}
