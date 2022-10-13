#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace Skyers
{
	class Shader : public Resource
	{
	public:
		~Shader();

		// Inherited via Resource
		virtual bool Create(std::string name, ...) override;

		GLuint m_shader = 0;

	};
}
