#include "VAO.h"
#include "VBL.h"
#include "Renderer.h"

VAO::VAO() {
	GLCall(glGenVertexArrays(1, &m_RendererID));
	//GLCall(glBindVertexArray(m_RendererID));
}

VAO::~VAO() {
	GLCall(glDeleteVertexArrays(1,&m_RendererID));
}

void VAO::AddBuffer(const VBO& vbo, const VBL& layout) {
	Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size();i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VAO::Bind() const {
	GLCall(glBindVertexArray(m_RendererID));
}
void VAO::Unbind() const {
	GLCall(glBindVertexArray(0));
}