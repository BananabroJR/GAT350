#include "Engine.h" 
#include <iostream> 

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("Application Started");
	Skyers::InitializeMemory();
	Skyers::SetFilePath("../Assesets");

	Skyers::Engine::Instance().Initialize();
	Skyers::Engine::Instance().Register();

	LOG("Engine Initilised");

	Skyers::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Made");

	
	//create vertex buffer
	

	auto m = Skyers::g_resources.Get<Skyers::Model>("Models/ogre.obj");

	std::shared_ptr<Skyers::Material> material = Skyers::g_resources.Get<Skyers::Material>("Materials/ogre.mtrl");
	material->Bind();
	
	//material->GetProgram()->SetUniform("model", glm::mat4(1));
	//material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	//material->GetProgram()->SetUniform("scale", 0.5f);

	
	glm::mat4 model{1};
	glm::mat4 projection = glm::perspective(45.0f, Skyers::g_renderer.GetWidth() / (float)Skyers::g_renderer.GetHeight(), 0.01f,100.0f);
	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 4 };

	std::vector<Skyers::Transform> transform;
	for (size_t i = 0; i < 10; i++)
	{
		transform.push_back({ { Skyers::randomf(-10,10),Skyers::randomf(-10,10),Skyers::randomf(-10,10)},{Skyers::random(360) , Skyers::random(360) , Skyers::random(360)}});
	}
	

	bool quit = false;
	while (!quit)
	{
		Skyers::Engine::Instance().Update();
		float speed = 3;

		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_escape) == Skyers::InputSystem::KeyState::Pressed) quit = true;
		//add input to move camera (I will do this after i go to tutoring and get the box to draw at all)



		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_left) == Skyers::InputSystem::KeyState::Held) cameraPosition.x -= speed * Skyers::g_time.deltaTime;
		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_right) == Skyers::InputSystem::KeyState::Held)cameraPosition.x += speed * Skyers::g_time.deltaTime;
		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_down) == Skyers::InputSystem::KeyState::Held)cameraPosition.y -= speed * Skyers::g_time.deltaTime;
		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_up) == Skyers::InputSystem::KeyState::Held)cameraPosition.y += speed * Skyers::g_time.deltaTime;
		

		//model = glm::eulerAngleXYX(0.0f, Skyers::g_time.time,0.0f);

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });

		glm::mat4 mvp = projection * view * glm::mat4(1);
		material->GetProgram()->SetUniform("mvp", mvp);


		Skyers::g_renderer.BeginFrame();

		m->m_vertexBuffer.Draw();
	//	for (size_t i = 0; i < transform.size(); i++)
		//{
		//	transform[i].rotation += glm::vec3{ 0,90 * Skyers::g_time.deltaTime,0 };

		//	glm::mat4 mvp = projection * view * (glm::mat4)transform[i];
		//	material->GetProgram()->SetUniform("mvp", mvp);

		//	vb->Draw();

		//}
		
		Skyers::g_renderer.EndFrame();
	}

	Skyers::Engine::Instance().Shutdown();

	return 0;
}