#include "VBO.h"
#include "Renderer.h"

VBO::VBO(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VBO::~VBO() {
	GLCall(glDeleteBuffers(1, &m_ID));
}

void VBO::Bind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VBO::Unbind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}