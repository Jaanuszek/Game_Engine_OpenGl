#ifndef SOLID_H
#define SOLID_H

#include "VBO.h"

class Solid {
protected:
	Vertex *vertices; //the size of array should depend on objects vertices size. Work on it !!!
	unsigned int verticesSize;
	unsigned int *indices;
	unsigned int indicesSize;
	virtual void Initalize() = 0;
public:
	Solid() : verticesSize(0), indicesSize(0) {}
	virtual ~Solid() {
		delete[] vertices;
		delete[] indices;
	}
	const Vertex* GetVerticesStruct(void) const{
		return vertices;
	}
	const unsigned int GetVerticesSize(void) const{
		return verticesSize/sizeof(Vertex);
	}
	const unsigned int* GetIndices(void) const{
		return indices;
	}
	const unsigned int GetIndicesSize(void) const{
		return indicesSize/sizeof(unsigned int);
	}
};
#endif