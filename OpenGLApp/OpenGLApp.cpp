// OpenGLApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "glad.h"  
#include <GLFW/glfw3.h> 

#include <iostream>

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


    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

    printf("GL: %i.%i\n", GLVersion.major, GLVersion.minor);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*

int main()
{
    std::cout << "Hello World!\n";
    return 0;
}

*/
