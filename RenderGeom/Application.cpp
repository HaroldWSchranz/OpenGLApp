#include "Application.h"

#include "glad.h"  
#include <GLFW/glfw3.h> 

#include "Gizmos.h" 
#include <glm/glm.hpp> 
#include <glm/ext.hpp>

#include <iostream>

namespace harry {
    using glm::vec3;
    using glm::vec4;
    using glm::mat4;

    using aie::Gizmos;

    bool Application::startup()
    {
        if (glfwInit() == false)
            return false;

        m_window = glfwCreateWindow(m_width, m_height,
            m_title,
            nullptr, nullptr);

        if (m_window == nullptr) {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);

        // the rest of our code goes here! 

        if (!gladLoadGL()) {
            glfwDestroyWindow(m_window);
            glfwTerminate();
            return false;
        }

        printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

        glClearColor(0.25f, 0.25f, 0.25f, 1);
        glEnable(GL_DEPTH_TEST); // enables the depth buffer

        Gizmos::create(10000, 10000, 0, 0);
        m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
        m_projection = glm::perspective(glm::pi<float>() * 0.25f,
            16 / 9.f, 0.1f, 1000.f);
        return true;
    }

    bool Application::update()
    {
        return (glfwWindowShouldClose(m_window) == false &&
            glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
    }

    void Application::shutdown()
    {
        Gizmos::destroy();

        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Application::setBackgroundColour(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    unsigned int Application::getWindowWidth() const {
        int w = 0, h = 0;
        glfwGetWindowSize(m_window, &w, &h);
        return w;
    }

    unsigned int Application::getWindowHeight() const {
        int w = 0, h = 0;
        glfwGetWindowSize(m_window, &w, &h);
        return h;
    }

}

