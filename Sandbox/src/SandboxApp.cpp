#include "Lynton.h"


class ExampleLayer : public Lynton::Layer
{
public:
	ExampleLayer()
	    : Layer("Example") {}

	void on_update() override
	{
		LY_INFO("ExamleLayer::Update");
	}

	void on_event(Lynton::Event& event) override
	{
		LY_TRACE("{0}", event);
	}
};


class Sandbox : public Lynton::Application
{
public:
	Sandbox()
	{
		push_layer(new ExampleLayer());
		push_overlay(new Lynton::ImGuiLayer());
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
