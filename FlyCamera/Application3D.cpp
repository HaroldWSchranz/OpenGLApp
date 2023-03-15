#include "Application3D.h"

#include "glad.h"
#include <GLFW/glfw3.h> 

#include "Gizmos.h" 
#include <glm/glm.hpp> 
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

using aie::Gizmos;

Application3D::~Application3D()
{
}

bool Application3D::startup() {
    Application::startup();
    setBackgroundColour(0.25f, 0.25f, 0.25f);

    // initialise gizmo primitive counts 
    Gizmos::create(10000, 10000, 10000, 10000);

    // create simple camera transforms 
    //m_view = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
    //m_view = glm::lookAt(vec3(16, 16, 24), vec3(-8,-8,-8), vec3(0, 1, 0));
    //m_view = glm::lookAt(vec3(24, 24, 24), vec3(-0, 4, -2), vec3(0, 1, 0));
    //m_view = glm::lookAt(vec3(20,20,24), vec3(-2,-2,-2), vec3(0, 1, 0));
    //m_projection = glm::perspective(glm::pi<float>() * 0.25f,
    //    getWindowWidth() / (float)getWindowHeight(),
    //    0.1f, 1000.f);

    m_shader.loadShader(aie::eShaderStage::VERTEX,
        "./shaders/simple.vert");
    m_shader.loadShader(aie::eShaderStage::FRAGMENT,
        "./shaders/simple.frag");
    if (m_shader.link() == false) {
        printf("Shader Error: %s\n", m_shader.getLastError());
        return false;
    }

    //m_quadMesh.initialiseQuad();
    // ================================================================================
    // create a quad using our new method by simply passing in the vertex data manually: 
    // define 6 vertices for 2 triangles 
    //Mesh::Vertex vertices[6];
    //vertices[0].position = { -0.5f, 0, 0.5f, 1 };
    //vertices[1].position = { 0.5f, 0, 0.5f, 1 };
    //vertices[2].position = { -0.5f, 0, -0.5f, 1 };
    //
    //vertices[3].position = { -0.5f, 0, -0.5f, 1 };
    //vertices[4].position = { 0.5f, 0, 0.5f, 1 };
    //vertices[5].position = { 0.5f, 0, -0.5f, 1 };
    //
    //m_quadMesh.initialise(6, vertices);
    // ================================================================================
    // make use of indices as well if we wanted:
    // define 4 vertices for 2 triangles 
    //Mesh::Vertex vertices[4];
    //vertices[0].position = { -0.5f, 0, 0.5f, 1 };
    //vertices[1].position = { 0.5f, 0, 0.5f, 1 };
    //vertices[2].position = { -0.5f, 0, -0.5f, 1 };
    //vertices[3].position = { 0.5f, 0, -0.5f, 1 };
    //
    //unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
    //
    //m_quadMesh.initialise(4, vertices, 6, indices);
    //// make the quad 10 units wide 
    //m_quadTransform = {
    // 10,0,0,0,
    // 0,10,0,0,
    // 0,0,10,0,
    // 0,0,0,1 };
    // ================================================================================
    
    m_quadMesh.initialiseFromFile("stanford/bunny.obj");
    //m_quadMesh2.initialiseFromFile("stanford/Dragon.obj");
    //m_quadMesh.initialiseFromFile("stanford/Buddha.obj");
    //m_quadMesh.initialiseFromFile("stanford/Lucy.obj");
    //m_quadMesh.initialiseFromFile("stanford/Turret.obj");
 
    // make the bunny smaller 1 units wide 
    m_quadTransform = {
     1,0,0,0,
     0,1,0,0,
     0,0,1,0,
     0,0,0,1 };

    return true;
}

void Application3D::shutdown()
{
}

bool Application3D::update(float deltaTime)
{
    return Application::update();
}

void Application3D::draw()
{
    // our game logic and update code goes here! 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Gizmos::clear();

    Gizmos::addTransform(glm::mat4(1));

    float windowWidth = Application::getWindowWidth();
    float windowHeight = Application::getWindowHeight();

    glm::mat4 pv = m_camera.getProjectionMatrix(windowWidth, windowHeight) *
        m_camera.getViewMatrix();

    // bind shader
    m_shader.bind();

    // bind transform
    auto pvm = pv * m_quadTransform;
    m_shader.bindUniform("ProjectionViewModel", pvm);

    // draw quad
    m_quadMesh.draw();

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

    //Gizmos::draw(m_projection * m_view);
    Gizmos::draw(pv);

    // bind shader 
    m_shader.bind();

    // bind transform 
    //auto pvm = m_projection * m_view * m_quadTransform;
    //m_shader.bindUniform("ProjectionViewModel", pvm);

    // draw quad 
    m_quadMesh.draw();

    glfwSwapBuffers(m_window);
    glfwPollEvents();

    // so does our render code! 


}
