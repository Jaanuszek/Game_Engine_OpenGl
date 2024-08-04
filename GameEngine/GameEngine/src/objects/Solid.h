#ifndef SOLID_H
#define SOLID_H

#include "VBO.h"

class Solid {
protected:
	Vertex* vertices;
	unsigned int verticesSize;
	unsigned int* indices;
	unsigned int indicesSize;
public:
	Solid() : vertices(nullptr), verticesSize(0), indices(nullptr), indicesSize(0) {}
	virtual ~Solid() {
		delete[] vertices;
		delete[] indices;
	}
	Vertex* GetVerticesStruct() {
		return vertices;
	}
	unsigned int GetVerticesSize() {
		return verticesSize;
	}
	unsigned int* GetIndices(){
		return indices;
	}
	unsigned int GetIndicesSize() {
		return indicesSize;
	}
	virtual void Initalize() = 0;
};
#endif