#include "Lynton.h"

// #include "imgui/imgui.h"


class ExampleLayer : public Lynton::Layer
{
public:
	ExampleLayer()
	    : Layer("Example") {}

	void on_update() override
	{
		Lynton::Application::get().get_running() = !Lynton::Input::is_key_pressed(LY_KEY_TAB);
	}

	// Lynton has to become a static library for this to work
	// void on_imgui_render() override
	// {
	// 	ImGui::Begin("Test");
	// 	ImGui::Text("Hello World");
	// 	ImGui::End();
	// }

	void on_event(Lynton::Event& event) override
	{
		if (event.get_event_type() == Lynton::EventType::key_pressed)
		{
			Lynton::KeyPressedEvent& e = (Lynton::KeyPressedEvent&)event;
			LY_TRACE("{0}", (char)e.get_key_code());
		}
	}
};


class Sandbox : public Lynton::Application
{
public:
	Sandbox()
	{
		push_layer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Lynton::Application* Lynton::create_application()
{
	return new Sandbox();
}

/*
 * $(TEMP)vc$(PlatformToolsetVersion).pdb has to be added in every projects property page under C/C++ -> Output Files -> Program Database File Name
 */
