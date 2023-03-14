#pragma once
#include <glm/glm.hpp>

// forward declared structure for access to GLFW window
struct GLFWwindow;

class Application
{
public:
	Application(const char* title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;
	}


public:
	bool startup();
	bool update();
	void draw();
	void shutdown();

protected:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	GLFWwindow* m_window;

	const char* m_title;
	int m_width;
	int m_height;
};

