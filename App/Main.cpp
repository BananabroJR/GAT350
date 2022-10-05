#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
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
		
		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		Skyers::g_renderer.EndFrame();
	}

	Skyers::Engine::Instance().Shutdown();

	return 0;
}