#pragma once
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

		// sets the colour that the sceen is cleared to
		void setBackgroundColour(float r, float g, float b, float a = 1.0f);

		// returns the width / height of the game window
		unsigned int getWindowWidth() const;
		unsigned int getWindowHeight() const;

	protected:
		glm::mat4 m_view;
		glm::mat4 m_projection;

		GLFWwindow* m_window;

		const char* m_title;
		int m_width;
		int m_height;
	};

}
