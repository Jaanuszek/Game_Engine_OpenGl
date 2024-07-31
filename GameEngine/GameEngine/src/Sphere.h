#pragma once

#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "VBO.h"

class Sphere {
private:
	std::vector<Vertex> verticesSphereVertex;
	std::vector<float> verticesSphere;
	std::vector<unsigned int> indicesSphere;
	void RenderSphere(float radius, unsigned int sectors, unsigned int stacks, std::vector<float>& vertices, std::vector<unsigned int>& indices);
public:
	Sphere(float radius, unsigned int sectors, unsigned int stacks);
	const std::vector<float>& GetVertices(void) const;
	const std::vector<unsigned int>& GetIndices(void) const;
};