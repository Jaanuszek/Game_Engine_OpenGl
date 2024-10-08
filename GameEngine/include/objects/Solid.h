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
	std::vector<unsigned int> indices;
	bool m_isUpdated = false;

	virtual void Initalize() = 0;
	std::vector<float> getUnitCircleVertices(unsigned int sectorCount);
public:
	virtual ~Solid() = default;
	virtual void UpdateVerticesAndIndices() = 0;
	virtual void UpdateParams() = 0;
	const std::vector<Vertex>& GetVertices(void) const { return vertices; }
	// I removed const because its not necesary since it returns a copy to this object
	// But this second const is meaningful becasue it says that my method is not going to modify the object
	size_t GetVerticesSize(void) const { return vertices.size(); } 
	// But right there the first const is meaningful because we are returning a reference (pointer) so we are telling that the pointer is not going to be modified
	const std::vector<unsigned int>& GetIndices(void) const { return indices; }
	size_t GetIndicesSize(void) const { return indices.size(); }
	void SetIsUpdated(const bool& isUpdated) { m_isUpdated = isUpdated; }
	bool GetIsUpdated(void) const { return m_isUpdated; }
};
#endif