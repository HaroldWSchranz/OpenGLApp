#include "Mesh.h"
#include "glad.h"
#include <cassert>	// https://www.programiz.com/cpp-programming/assertions
// In C++, an assertion is a statement used to state or assert that the expression must be true.
// It is used to check the conditions that cannot happen unless there is a bug.So, 
// it is used as a debugging tool since it terminates the program when the assertion becomes false.
//
// define the desctructor, initialiseQuad and draw methods. 
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad() {
	// check that the mesh is not initialized already 
	assert(vao == 0);

	// generate buffers 
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array aka a mesh wrapper 
	glBindVertexArray(vao);

	// bind vertex buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// define 6 vertices for 2 triangles 
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	// fill vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	// enable first element as position 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);

	// unbind buffers 
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles 
	triCount = 2;
}

void Mesh::draw() {
	glBindVertexArray(vao);
	// using indices or just vertices? 
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount,
			GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}



/*

squiggles with assert

Binding marks something as “active” in OpenGL, either active for editing or active for drawing by sending it to the GPU.

Since we’re creating a quad, which is two triangles, and since we’re not using an index buffer, we will
need 6 vertices, 3 for each triangle.


possible includes?

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



#include "Gizmos.h"
//#include "gl_core_4_4.h"
#include "glad.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>


*/