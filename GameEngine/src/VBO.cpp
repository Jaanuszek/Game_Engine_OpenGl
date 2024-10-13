#include "VBO.h"
#include "Renderer.h"


VBO::VBO(std::vector<Vertex>& vertices)
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	m_currentSizeOfBuffer = vertices.size() * sizeof(Vertex);
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_currentSizeOfBuffer, vertices.data(), GL_DYNAMIC_DRAW));
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

void VBO::Update(const std::vector<Vertex>& vertices) {
	unsigned int updatedSize = vertices.size() * sizeof(Vertex);
	Bind();
	if (updatedSize != m_currentSizeOfBuffer) {
		GLCall(glBufferData(GL_ARRAY_BUFFER, updatedSize, vertices.data(), GL_DYNAMIC_DRAW));
		m_currentSizeOfBuffer = updatedSize;
	}
	else {
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, updatedSize, vertices.data()))
	}
}
