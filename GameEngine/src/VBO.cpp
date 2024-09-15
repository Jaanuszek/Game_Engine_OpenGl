#include "VBO.h"
#include "Renderer.h"
#include <iostream>

VBO::VBO(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

VBO::VBO(std::vector<Vertex>& vertices)
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	//GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
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

void VBO::Update(const void* data, unsigned int size) const
{

	//if you want to resize the size of buffer you have to call glBufferData with the same ID but different size
	//then u can use glBufferSubData.
	//wrtie a algorithm that will check wheter it is necessary to update the buffer size or not (I think it would be awesome for performace)
	// https://learnopengl.com/Advanced-OpenGL/Advanced-Data
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data)); //update the whole data of buffer
}

void VBO::Update(std::vector<Vertex>& vertices) {
	unsigned int updatedSize = vertices.size() * sizeof(Vertex);
	// Basically there is no option to increase the VBO buffer size.
	// TODO optimization to be done here
	// There is issue, when i have 120fps everything is fine, but when i have 60fps, the buffer is not updated properly
	// it can be repaired by implementing double-buffering or streaming buffer
	Bind();
	if (updatedSize != m_currentSizeOfBuffer) {
		GLCall(glBufferData(GL_ARRAY_BUFFER, updatedSize, vertices.data(), GL_DYNAMIC_DRAW));
		m_currentSizeOfBuffer = updatedSize;
	}
	else {
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, updatedSize, vertices.data()))
	}
}
