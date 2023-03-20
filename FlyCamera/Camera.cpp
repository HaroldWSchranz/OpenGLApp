#include "Application.h"
#include "Camera.h"

#include <GLFW/glfw3.h> 
 

// OpenGL provides a handy function for doing this, with glm::lookAt, which constructs a view matrix
// from a position, another position that we’re looking at (position + forward will do here) and an up vector.
glm::mat4 Camera::getViewMatrix()
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
    return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}


// The perspective matrix can be calculated from a field of view, screen width and height
// for aspect ratio, and near and far plane values. Here we’ve specified a 90 degree (PI/4) field of view.
// We could turn this into a member variable if we plan to change the field of view at run time or for different cameras.
glm::mat4 Camera::getProjectionMatrix(float w, float h)
{
    return glm::perspective(glm::pi<float>() * 0.25f,
        w / h,
        0.1f, 1000.f);
}

// The code for translating the camera in its update function should look like this: (not sure if it should be void/bool)
bool Camera::update(float deltaTime, GLFWwindow* window)
{
    float thetaR = glm::radians(m_theta);
    float phiR = glm::radians(m_phi);
    //calculate the forwards and right axes and up axis for the camera
    glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
    glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
    glm::vec3 up(0, 1, 0);
    // use WASD, ZX keys to move camera around
    if (glfwGetKey(window, GLFW_KEY_W))
        m_position += forward * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S))
        m_position -= forward * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_D))
        m_position += right * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A))
        m_position -= right * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_Z))
        m_position -= up * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_X))
        m_position += up * deltaTime;

    glm::vec2 mouseDelta = harry::Application::get()->getMouseDelta();  // CHECK THIS!!! added harry namespace
    const float turnSpeed = 0.1f;
    // if the right button is down, increment theta and phi
    if (glfwGetMouseButton(window, 1))
    {
        m_theta += turnSpeed * mouseDelta.x;
        m_phi -= turnSpeed * mouseDelta.y;
    }
    return true;
}


/*
You’ll probably also want to add code to clamp m_phi between values of say -70 and 70 degrees to
prevent gimbal lock

Camera.cpp has Camera.h and Application.h
Application.h has Camera.h

You’ll also want to initialise the position and angles of your Camera. At the very least, set m_theta
and m_phi to zero, which leaves the camera looking down the x-axis. A good start value for
m_position would be (-10, 2, 0), putting it above the plane and looking towards the origin.
You can do better than that by providing a constructor that takes initial position and angles, or
accessors, and setting them that way.


*/