#include "Mesh.h"

Mesh::Mesh(const float* vertices, GLsizei vertexCount, const unsigned int* indices, GLsizei indexCount)
	: m_VBO(vertices, vertexCount), m_EBO(indices, indexCount), m_Count(indexCount) //????
{

}

Mesh::~Mesh()
{
}
