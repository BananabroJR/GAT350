#include "Engine.h" 
#include <iostream> 

int main()
{
	Skyers::InitializeMemory();

	Skyers::Engine::Instance().Initialize();
	Skyers::Engine::Instance().Register();

	Skyers::g_renderer.CreateWindow("Neumont", 800, 600);

	bool quit = false;
	while (!quit)
	{
		Skyers::Engine::Instance().Update();

		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_escape) == Skyers::InputSystem::KeyState::Pressed) quit = true;

		Skyers::g_renderer.BeginFrame();
		Skyers::g_renderer.EndFrame();
	}

	Skyers::Engine::Instance().Shutdown();
}