#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>

// forward declared structure for access to GLFW window
struct GLFWwindow;

namespace harry {
	class Application
	{
	public:
		Application(const char* title, int width, int height)
		{
			m_title = title;
			m_width = width;
			m_height = height;
		}

		bool startup();
		bool update();
		virtual void draw() = 0;
		void shutdown();

		// singleton pattern
		static Application* get() { return s_instance; }
		glm::vec2 getMousePosition() { return m_mousePosition; }
		glm::vec2 getMouseDelta() // the amount that the mouse has moved this frame
			{ return m_mousePosition - m_lastMousePosition; }

		// set up mouse input
		static void SetMousePosition(GLFWwindow* window, double x, double y);
		//

		// sets the colour that the sceen is cleared to
		void setBackgroundColour(float r, float g, float b, float a = 1.0f);

		// returns the width / height of the game window
		unsigned int getWindowWidth() const;
		unsigned int getWindowHeight() const;

	protected:
		static Application* s_instance;

		GLFWwindow* m_window;

		aie::ShaderProgram m_shader;
		Mesh m_quadMesh;
		glm::mat4 m_quadTransform;

		glm::vec2 m_mousePosition;
		glm::vec2 m_lastMousePosition; // storing the last mouse position

		Camera m_camera;

		//glm::mat4 m_view;
		//glm::mat4 m_projection;

		const char* m_title;
		int m_width;
		int m_height;
	};

}

/*
Add a Camera member variable to your application class, replacing the m_viewMatrix and
m_projectionMatrix members. Find any references to these variables and remove them

We can now calculate projectionMatrix and viewMatrix as local variables inside the application
draw() function.

*/

/*

class Application
{
public:
bool startup();
bool update();
void draw();
void shutdown();
// singleton pattern
static Application* get() { return s_instance; }
glm::vec2 getMousePosition() { return m_mousePosition; }
// set up mouse input
static void SetMousePosition(GLFWwindow* window, double x, double y);
protected:
static Application* s_instance;
GLFWwindow* m_window;
aie::ShaderProgram m_shader;
Mesh m_quadMesh;
glm::mat4 m_quadTransform;
glm::vec2 m_mousePosition;
Camera m_camera;
};

*/