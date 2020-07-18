#include "Lynton.h"


class Sandbox : public Lynton::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Lynton::Application* Lynton::create_application()
{
	return new Sandbox();
}