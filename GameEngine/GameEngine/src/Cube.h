#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VBO.h"

struct VertexCube {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Color;
	glm::vec3 Normal;
};

class Cube{
private:
	Vertex verticesCu[6*4] = {
		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},	
		{glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		{glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,0.0f,-1.0f)},

		{glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,0.0f,1.0f)},

		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		{glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(-1.0f,0.0f,0.0f)},
		{glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		{glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},

		{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},
		{glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(1.0f,0.0f,0.0f)},
		{glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f)},
		{glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},

		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		{glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		{glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,-1.0f,0.0f)},

		{glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
		{glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
		{glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0,1.0f,0.0f)},	
		{glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0,1.0f,0.0f)}
	};

	Vertex verticesTest[6*4] = {
		Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,-1.0f)},
		Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,0.0f,-1.0f)},

		Vertex {glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
		Vertex {glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f)},
		Vertex {glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f)},
		Vertex {glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,0.0f,1.0f)},

		Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(-1.0f,0.0f,0.0f)},
		Vertex {glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(-1.0f,0.0f,0.0f)},
		Vertex {glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(-1.0f,0.0f,0.0f)},

		Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},
		Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(1.0f,0.0f,0.0f)},
		Vertex {glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(1.0f,0.0f,0.0f)},
		Vertex {glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f)},

		Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		Vertex {glm::vec3(0.5f,-0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(0.0f,-1.0f,0.0f)},
		Vertex {glm::vec3(-0.5f,-0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f,-1.0f,0.0f)},

		Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
		Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0,1.0f,0.0f)},
		Vertex {glm::vec3(0.5f,0.5f,0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0,1.0f,0.0f)},
		Vertex {glm::vec3(-0.5f,0.5f,0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0,1.0f,0.0f)}
	};
	float verticesCube[6 * 4 * 11] = {
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f,-1.0f, // left bottom back
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,-1.0f, // right bottom back
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,-1.0f, // right top back
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f,0.0f,-1.0f, // left top back

		// Front face
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.2f, 0.5f, 0.7f, 0.0f, 0.0f, 1.0f, // left bottom front
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,// right bottom front
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,// right top front
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.7f, 0.5f, 0.2f, 0.0f, 0.0f, 1.0f,// left top front

		// Left face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // left bottom back
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, // left top back
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.7f, 0.5f, 0.2f, -1.0f, 0.0f, 0.0f, // left top front
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 0.7f, -1.0f, 0.0f, 0.0f, // left bottom front

		// Right face
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // right bottom back
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,// right top back
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// right top front
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// right bottom front

		 // Bottom face
		 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // left bottom back
		  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// right bottom back
		  0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// right bottom front
		 -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 0.7f, 0.0f, -1.0f, 0.0f,// left bottom front

		 // Top face
		 -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,// left top back
		  0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// right top back
		  0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// right top front
		 -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.7f, 0.5f, 0.2f, 0.0f, 1.0f, 0.0f,// left top front
	};

	unsigned int indicesCube[6 * 2 * 3] = {
		// Back face
		0, 1, 2,
		2, 3, 0,
		// Front face
		4, 5, 6,
		6, 7, 4,
		// Left face
		8, 9, 10,
		10, 11, 8,
		// Right face
		12, 13, 14,
		14, 15, 12,
		// Bottom face
		16, 17, 18,
		18, 19, 16,
		// Top face
		20, 21, 22,
		22, 23, 20
	};
public:
	const float* GetVertices(void) const {
		return verticesCube;
	}
	const unsigned int* GetIndices(void) const {
		return indicesCube;
	}
	const unsigned int GetVerticesSize(void) const {
		return sizeof(verticesCube)/sizeof(float);
	}
	const unsigned int GetIndicesSize(void) const {
		return sizeof(indicesCube)/sizeof(unsigned int);
	}
	const Vertex* GetVerticesStruct(void) const {
		return verticesCu;
	}
	const unsigned int GetVerticesStructSize(void) const {
		return sizeof(verticesCu)/sizeof(Vertex);
	}
	const Vertex* GetVerticesTest(void) const {
		return verticesTest;
	}
};