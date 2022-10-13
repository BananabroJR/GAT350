#include "Engine.h" 
#include <iostream> 

float points[] = {
  -1.0f, -0.5f,  0.0f,
   -1.0f,  0.5f,  0.0f,
   1.0f, -1.0f,  0.0f,

   -1.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, -1.0f, 0.0f
  
};

Skyers::Vector3 colors[] = {
	{0,0,1},
	{1,0,1},
	{0,1,1},
	{1,0,0},
	{0,0,1},
	{0,1,1}
};

glm::uvec2 texcoords[]
{
	{0,0},
	{0,1},
	{1,0},
	{0,1},
	{1,1},
	{1,0},
};

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position * 0.2, 1.0);"
"}";



const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0, 1.0, 0.0, 1.0);"
"  color = vec4(1.0, 1.0, 0.0, 1.0);"
"}";

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

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	std::shared_ptr<Skyers::Shader> vs = Skyers::g_resources.Get<Skyers::Shader>("Shader/basic.vert",GL_VERTEX_SHADER);
	std::shared_ptr<Skyers::Shader> fs = Skyers::g_resources.Get<Skyers::Shader>("Shader/basic.frag",GL_FRAGMENT_SHADER);


	/*GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);*/

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);


	GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");

		
	glUniform3f(uniform2, 1,0,0);

	

	glm::mat4 mx{1};

	bool quit = false;
	while (!quit)
	{
		Skyers::Engine::Instance().Update();

		if (Skyers::g_inputSystem.GetKeyState(Skyers::key_escape) == Skyers::InputSystem::KeyState::Pressed) quit = true;

		glUniform1f(uniform1,std::sin(Skyers::g_time.time));
		mx = glm::eulerAngleXYX(0.0f,0.0f,Skyers::g_time.time);
		glUniformMatrix4fv(uniform3, 1,GL_FALSE,glm::value_ptr(mx));
		
		Skyers::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		

		Skyers::g_renderer.EndFrame();
	}

	Skyers::Engine::Instance().Shutdown();

	return 0;
}