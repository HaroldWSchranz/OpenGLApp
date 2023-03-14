// OpenGLApp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Application.h" 

const int windowWidth = 1280;
const int windowHeight = 720;

int main() {

    Application* theApp = new Application("Title", windowWidth, windowHeight);
    if (theApp->startup() == true) {
        while (theApp->update() == true)
            theApp->draw();
        theApp->shutdown();
    }

    delete theApp;
    return 0;
}




/*

#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;

const int windowWidth = 1280;
const int windowHeight = 720;
int main() {

    if (glfwInit() == false)
        return -1;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight,
        "Computer Graphics",
        nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);

    // the rest of our code goes here!

    printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

    glClearColor(0.25f, 0.25f, 0.25f, 1);
    glEnable(GL_DEPTH_TEST); // enables the depth buffer

    Gizmos::create(10000, 10000, 0, 0);
    mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
    mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
        16 / 9.f, 0.1f, 1000.f);

    while (glfwWindowShouldClose(window) == false &&
        glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // our game logic and update code goes here!
        while (glfwWindowShouldClose(window) == false &&
            glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

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

            Gizmos::draw(projection * view);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        // so does our render code!

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Gizmos::destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


*/


/*
In the past this was a complicated process, but thanks to tools like Glad it is a simple process to
remap all of OpenGL’s function calls to the correct versions and feature sets. After we have a
window created we simply call gladLoadGL():

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
