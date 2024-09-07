#include "VBO.h"
#include "Renderer.h"

VBO::VBO(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VBO::VBO(std::vector<Vertex>& vertices)
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
	//GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW));
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

void VBO::Update(const void* data, unsigned int size) const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data)); //update the whole data of buffer
}
