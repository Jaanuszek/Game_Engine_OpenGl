#pragma once

#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"


class Mesh {
private:
	VAO m_VAO;
	VBO m_VBO;
	EBO m_EBO;
	GLsizei m_Count;
public:
	Mesh(const float* vertices, GLsizei vertexCount, const unsigned int* indices = nullptr, GLsizei indexCount = 0);
	~Mesh();

};