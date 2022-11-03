#include "Engine.h" 
#include <iostream> 

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


	// load scene 
	auto scene = std::make_unique<Skyers::Scene>();

	rapidjson::Document document;
	bool success = Skyers::json::Load("scenes/basic_lit.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/basic_lit.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}
		
	//create the model
	//auto scene = Skyers::g_resources.Get<Skyers::Scene>("Scenes/basic.scn");
	
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
		
		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_escape) == Skyers::InputSystem::KeyState::Pressed) quit = true;


		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation.y += Skyers::g_time.deltaTime * 90.0f;
		}

		scene->Update();

		Skyers::g_renderer.BeginFrame();

		scene->Draw(Skyers::g_renderer);
	
		
		Skyers::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	Skyers::Engine::Instance().Shutdown();

	return 0;
}