#include "EBO.h"
#include "Renderer.h"

EBO::EBO(const std::vector<unsigned int>& indices) : m_Count()
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	m_CurrentSize = indices.size() * sizeof(unsigned int);
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_CurrentSize, indices.data(), GL_DYNAMIC_DRAW));
}

EBO::~EBO() {
	GLCall(glDeleteBuffers(1, &m_ID));
}

void EBO::Bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID)) ;
}

void EBO::Unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void EBO::Update(const std::vector<unsigned int>& indices)
{
	unsigned int updatedSize = indices.size() * sizeof(unsigned int);
	Bind();
	if (updatedSize != m_CurrentSize) {
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW));
		m_CurrentSize = updatedSize;
	}
	else {
		GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), indices.data()));
	}
}
