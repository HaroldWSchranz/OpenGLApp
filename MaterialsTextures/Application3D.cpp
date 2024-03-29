#include "Application3D.h"

#include "imgui_glfw3.h"

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

    // Within the application�s startup() method you should set the light�s colours to a suitable value.
    // For this example, we will use yellow for the light, and a dark gray for the ambient:
    //m_light.colour = { 1, 1, 0 };
    //m_ambientLight = { 0.25f, 0.25f, 0.25f };
    m_light.colour = { 1,1,1 };
    m_ambientLight = { 0.25f, 0.25f, 0.25f };

    m_gridTexture.load("textures/numbered_grid.tga");

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

    //m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
    //m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
    //if (m_shader.link() == false) {
    //    printf("Shader Error: %s\n", m_shader.getLastError());
    //    return false;
    //}

    //m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
    //m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
    m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phongdltute.vert");
    m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phongdltute.frag");

    if (m_phongShader.link() == false) {
        printf("Phong Shader Error: %s\n", m_phongShader.getLastError());
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
    // 3RD QUAD METHOD:
    // make use of indices as well if we wanted:
    // define 4 vertices for 2 triangles 
    Mesh::Vertex vertices[4];
    vertices[0].position = { -0.5f, 0, 0.5f, 1 };
    vertices[1].position = { 0.5f, 0, 0.5f, 1 };
    vertices[2].position = { -0.5f, 0, -0.5f, 1 };
    vertices[3].position = { 0.5f, 0, -0.5f, 1 };
    //
    unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
    //
    m_quadMesh.initialise(4, vertices, 6, indices);
    // make the quad 20 units wide 
    m_quadTransform = {
    20,0,0,0,
    0,20,0,0,
    0,0,20,0,
    0,0,0,1 };
    // ================================================================================
    //
    m_bunnyMesh.initialiseFromFile("stanford/bunny.obj");
    m_bunnyMesh.loadMaterial("stanford/bunny.mtl");
    // make the bunny smaller 1 units wide
    m_bunnyTransform = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };

    // load imaginary texture
    aie::Texture texture1;
    texture1.load("mytexture.png");
    // create a 2x2 black-n-white checker texture
    // RED simply means one colour channel, i.e. grayscale
    aie::Texture texture2;
    unsigned char texelData[4] = { 0, 255, 255, 0 };
    texture2.create(2, 2, aie::Texture::RED, texelData);

    return true;
}

void Application3D::shutdown()
{
}

bool Application3D::update(float deltaTime)
{
    // ImGui code:
    aie::ImGui_NewFrame();

    //Application::update();
    // query time since application started
    float time = glfwGetTime();
    // rotate light
    //m_light.direction = glm::normalize(vec3(glm::cos(time * 2), glm::sin(time * 2), 0));
    float light_direction_frequency = 0.25f;
    m_light.direction = glm::normalize(vec3(glm::cos(time * light_direction_frequency), glm::sin(time * light_direction_frequency), 0));

    ImGui::Begin("Light Settings");
    ImGui::DragFloat3("Sunlight Direction", &m_light.direction[0], 0.1f, -1.0f, 1.0f);
    //ImGui::DragFloat3("Sunlight Colour", &m_light().colour[0], 0.1f, 0.0f, 2.0f);
    ImGui::DragFloat3("Sunlight Colour", &m_light.colour[0], 0.1f, 0.0f, 2.0f);
    ImGui::End();

    return Application::update();
    //return true;
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
    //m_shader.bind();
    // bind phong shader program
    m_phongShader.bind();

    // m_phongShader.bindUniform("cameraPosition",
    //   vec3(glm::inverse(m_viewMatrix)[3]));
    // or
    m_phongShader.bindUniform("cameraPosition",
        m_camera.getPosition());

    // bind light
    m_phongShader.bindUniform("AmbientColour", m_ambientLight);
    m_phongShader.bindUniform("LightColour", m_light.colour);
    m_phongShader.bindUniform("LightDirection", m_light.direction);

    // bind transform for m_bunnyMesh and m_bunnyTransform
    auto pvm = pv * m_bunnyTransform;
    m_phongShader.bindUniform("ProjectionViewModel", pvm);
    m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);      // bind transforms for lighting
    m_phongShader.bindUniform("LightDirection", m_light.direction);
    //
    m_bunnyMesh.applyMaterial(&m_phongShader);
    m_bunnyMesh.draw();

    // draw quad
    // m_quadMesh
    // bind shader 
    //m_shader.bind();
    // bind transform 
    auto pvm2 = pv * m_quadTransform;
    //m_shader.bindUniform("ProjectionViewModel", pvm);
    m_phongShader.bindUniform("ProjectionViewModel", pvm2);
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

    ImGui::Render();

    glfwSwapBuffers(m_window);
    glfwPollEvents();

    // so does our render code! 

}
