#pragma once
#include <glm/glm.hpp> 
#include <glm/ext.hpp>

// forward declared structure for access to GLFW window
struct GLFWwindow;

//Camera class with a positionand two angles.
class Camera
{
public:
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float w, float h);
    bool update(float deltaTime, GLFWwindow* window);  // (not sure if it should be void/bool. I matched Application style)

private:
    float m_theta = 0.0f;
    float m_phi   = 0.0f;
    glm::vec3 m_position = glm::vec3(-20,2,0);
};

