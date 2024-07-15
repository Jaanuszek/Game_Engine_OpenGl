#include "Pyramid.h"

void Pyramid::calculateNormals()
{
	for (int i = 0; i < 5; i++) { //clearing normals just in case
		verticesPyr[i].Normal = glm::vec3(0.0f);
	}
	for (int i = 0; i < GetIndicesSize(); i += 3) {
		int verticeIndex = i / 3;

		int index0 = indicesPyramid[i];
		int index1 = indicesPyramid[i + 1];
		int index2 = indicesPyramid[i + 2];

		glm::vec3 v0 = verticesPyr[index0].Position;
		glm::vec3 v1 = verticesPyr[index1].Position;
		glm::vec3 v2 = verticesPyr[index2].Position;

		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		verticesPyr[verticeIndex].Normal += normal;
	}
	for (int i = 0; i < 5; i++) {
		verticesPyr[i].Normal = glm::normalize(verticesPyr[i].Normal);
	}
}

Pyramid::Pyramid()
{
	calculateNormals();
}
