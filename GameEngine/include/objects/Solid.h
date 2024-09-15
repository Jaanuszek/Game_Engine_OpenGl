#ifndef SOLID_H
#define SOLID_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VBO.h"
#include "imgui.h"

#define PI glm::pi<float>()

class Solid {
protected:
	std::vector<Vertex> vertices;
	unsigned int verticesSize;
	std::vector<unsigned int> indices;
	unsigned int indicesSize;
	virtual void Initalize() = 0;
	std::vector<float> getUnitCircleVertices(unsigned int sectorCount);
public:
	Solid() : vertices(0),verticesSize(0),indices(0), indicesSize(0) {}
	virtual ~Solid() {}
	virtual void UpdateVerticesAndIndices() = 0;
	virtual void UpdateParams() = 0;
	const std::vector<Vertex>& GetVertices(void) const { return vertices; }
	const unsigned int GetVerticesSize(void) const { return vertices.size(); }
	const std::vector<unsigned int>& GetIndices(void) const { return indices; }
	const unsigned int GetIndicesSize(void) const { return indices.size(); }
};
#endif