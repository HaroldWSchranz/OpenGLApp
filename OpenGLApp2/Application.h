#pragma once
class Application
{
public:
	bool startup();
	bool update();
	void draw();
	void shutdown();

protected:
	glm::mat4 m_view;
	glm::mat4 m_projection;

	GLFWwindow* m_window;
};

