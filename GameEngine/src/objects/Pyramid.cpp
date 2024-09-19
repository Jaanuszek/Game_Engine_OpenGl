#include "Pyramid.h"

void Pyramid::Initalize() {
	vertices = {
		Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(0.0f)},
		Vertex {glm::vec3(0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3(0.0f)},
		Vertex {glm::vec3(0.5f,0.5f,-0.5f), glm::vec2(1.0f,1.0f), glm::vec3(0.0f)},
		Vertex {glm::vec3(-0.5f,0.5f,-0.5f), glm::vec2(0.0f,1.0f), glm::vec3(0.0f)},
		Vertex {glm::vec3(0.0f,0.0f,0.5f), glm::vec2(0.5f,0.5f), glm::vec3(0.0f)}
	};
	indices = {
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
}

void Pyramid::CalculateNormals() {
	for (int i = 0; i < 5; i++) { //clearing normals just in case
		vertices[i].Normal = glm::vec3(0.0f);
	}
	for (int i = 0; i < GetIndicesSize(); i += 3) {
		int index0 = indices[i];
		int index1 = indices[i + 1];
		int index2 = indices[i + 2];

		glm::vec3 v0 = vertices[index0].Position;
		glm::vec3 v1 = vertices[index1].Position;
		glm::vec3 v2 = vertices[index2].Position;

		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		vertices[index0].Normal += normal;
		vertices[index1].Normal += normal;
		vertices[index2].Normal += normal;
	}
	for (int i = 0; i < 5; i++) {
		vertices[i].Normal = glm::normalize(vertices[i].Normal);
	}
}

Pyramid::Pyramid() {
	Initalize();
	CalculateNormals();
}
Pyramid::~Pyramid() {

}

void Pyramid::UpdateVerticesAndIndices() {

}

void Pyramid::UpdateParams() {

}