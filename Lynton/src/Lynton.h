// for use in Lynton client application

#pragma once

#include "lypch.h"

#include "Lynton/Layer.h"
#include "Lynton/ImGui/ImGuiLayer.h"

#include "Lynton/Application.h"
#include "Lynton/Log.h"

#include "Lynton/Input.h"
#include "Lynton/KeyCodes.h"

// renderer
#include "Lynton/Renderer/Renderer.h"
#include "Lynton/Renderer/RenderCommand.h"

#include "Lynton/Renderer/GraphicsContext.h"
#include "Lynton/Renderer/OrthographicCamera.h"
#include "Lynton/Renderer/Shader.h"

/////////////////
// entry point //
/////////////////

#ifdef LY_PLATFORM_WINDOWS
extern Lynton::Application* Lynton::create_application();

int main(int argc, char** argv)
{
	Lynton::Log::init();
	LY_CORE_INFO("Initialized Log!");
	
	Lynton::Application* app = Lynton::create_application();
	app->run();
	delete app;
}
#endif
