#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"

class Application3D : public harry::Application {
public:

	Application3D();

	Application3D(const char* title, int width, int height) : Application(title, width, height)
	{
	}

	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual bool update(float deltaTime);
	virtual void draw();

protected:

	//glm::mat4 m_view;
	//glm::mat4 m_projection;

	aie::ShaderProgram m_shader;
	Mesh     m_quadMesh;
	glm::mat4   m_quadTransform;
};
