#pragma once

#include "VBO.h"

class VBL;

class VAO {
private:
	unsigned int m_RendererID;
public:
	VAO();
	~VAO();

	void AddBuffer(const VBO& vbo, const VBL& layout);
	void Bind() const;
	void Unbind() const;
};