#include "Lynton.h"
#include <Lynton/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

#include "ExampleLayer.h"


class Sandbox : public Lynton::Application
{
public:
	Sandbox()
	    : Application("Sandbox")
	{
		// push_layer(new ExampleLayer());
		push_layer(new Sandbox2D());
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
