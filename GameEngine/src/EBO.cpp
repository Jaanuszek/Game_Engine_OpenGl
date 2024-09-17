#include "EBO.h"
#include "Renderer.h"

EBO::EBO(const unsigned int* data, unsigned int count) : m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
}

EBO::EBO(std::vector<unsigned int>& indices)
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

void EBO::Update(const unsigned int* data, unsigned int count)
{
	m_Count = count;
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ID));
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(unsigned int), data));
}

void EBO::Update(std::vector<unsigned int>& indices)
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
	//Unbind();
}
