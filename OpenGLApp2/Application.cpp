#include "Application.h"

#include "glad.h"  
#include <GLFW/glfw3.h> 

#include "Gizmos.h" 
#include <glm/glm.hpp> 
#include <glm/ext.hpp>

#include <iostream>

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
        glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS );
}

void Application::draw()
{
    while (glfwWindowShouldClose(m_window) == false &&
        glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // our game logic and update code goes here! 
        while (glfwWindowShouldClose(m_window) == false &&
            glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Gizmos::clear();

            Gizmos::addTransform(glm::mat4(1));

            vec4 white(1);
            vec4 black(0, 0, 0, 1);

            for (int i = 0; i < 21; ++i) {
                Gizmos::addLine(vec3(-10 + i, 0, 10),
                    vec3(-10 + i, 0, -10),
                    i == 10 ? white : black);

                Gizmos::addLine(vec3(10, 0, -10 + i),
                    vec3(-10, 0, -10 + i),
                    i == 10 ? white : black);
            }

            Gizmos::draw(m_projection * m_view);

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
        // so does our render code! 

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Application::shutdown()
{
    Gizmos::destroy();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}
