// for use in Lynton client application

#pragma once

#include "lypch.h"

#include "Lynton/Core/Layer.h"
#include "Lynton/ImGui/ImGuiLayer.h"

#include "Lynton/Core/Application.h"
#include "Lynton/Core/Log.h"

#include "Lynton/Core/Input.h"
#include "Lynton/Core/KeyCodes.h"

#include "Lynton/Core/TimeStep.h"

// renderer
#include "Lynton/Renderer/Renderer.h"
#include "Lynton/Renderer/RenderCommand.h"

#include "Lynton/Renderer/GraphicsContext.h"
#include "Lynton/Renderer/OrthographicCamera.h"
#include "Lynton/Renderer/OrthographicCameraController.h"
#include "Lynton/Renderer/Shader.h"

#include "Lynton/Renderer/Texture.h"

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
