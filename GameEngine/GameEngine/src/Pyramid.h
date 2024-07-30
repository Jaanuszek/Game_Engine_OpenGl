#pragma once
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VBO.h"

struct VertexPyramid {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Color;
	glm::vec3 Normal;
};

class Pyramid {
private:
	float verticesPyramid[8*5] = {
		//adding colors as layout 2
		-0.5f,-0.5f,-0.5f,0.0f,0.0f, 1.0f,0.0f,0.0f, //left bottom back 0
		0.5f,-0.5f,-0.5f,1.0f,0.0f, 0.0f, 1.0f, 0.0f, //right bottom back 1
		0.5f,0.5f,-0.5f,1.0f,1.0f, 0.0f, 0.0f,1.0f, //right top back 2
		-0.5f,0.5f,-0.5f,0.0f,1.0f, 0.5f,0.5f,0.5f, //left top back 3

		0.0f,0.0f,0.5f,0.5f,0.5f, 1.0f,1.0f,0.0f //top of the pyramid 4
	};
	unsigned int indicesPyramid[3*6] = {
		//back wall
		0,1,2,
		2,3,0,
		//left wall
		0,3,4,
		//right wall
		1,2,4,
		//front wall
		0,1,4,
		2,3,4
	};
	Vertex verticesPyr[5] = {
		{glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f)},
		{glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(0.0f)},
		{glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f)},
		{glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.5f,0.5f,0.5f), glm::vec3(0.0f)},
		{glm::vec3(0.0f,0.0f,0.5f), glm::vec2(0.5f,0.5f), glm::vec3(1.0f,1.0f,0.0f), glm::vec3(0.0f)}
	};
	void calculateNormals();
public:
	Pyramid();
	const float* GetVertices(void) const {
		return verticesPyramid;
	}
	const unsigned int* GetIndices(void) const {
		return indicesPyramid;
	}
	const float GetVerticesSize(void) const {
		return sizeof(verticesPyr)/sizeof(Vertex);
		//return 5*sizeof(Vertex);
	}
	const unsigned int GetIndicesSize(void) const {
		return sizeof(indicesPyramid) / sizeof(unsigned int);
	}
	const Vertex* GetVerticesStruct(void) const {
		return verticesPyr;
	}
};