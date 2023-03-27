#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Shader.h"

namespace aie { class ShaderProgram; }

//  simple mesh class that stores unsigned integers for a single VAO, VBO  and IBO,
//  along with an additional unsigned integer storing how many triangles out mesh has :
class Mesh {
public:

	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	// Add the following child structure to the Mesh class: 
	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	// material properties:
	glm::vec3 Ka; // ambient colour of the surface
	glm::vec3 Kd; // diffuse colour of the surface
	glm::vec3 Ks; // specular colour of the surface
	float specularPower; // tightness of specular highlights

	void initialiseQuad();

	void initialise(unsigned int vertexCount, const Vertex* vertices,
		unsigned int indexCount = 0,
		unsigned int* indices = nullptr);

	void initialiseFromFile(const char* filename);

	virtual void draw();

	void applyMaterial(aie::ShaderProgram* shader);

	void loadMaterial(const char* fileName);

protected:

	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

