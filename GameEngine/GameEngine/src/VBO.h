#pragma once

class VBO {
private:
	unsigned int m_ID;
public:
	VBO(const void* data, unsigned int size);
	~VBO();

	void Bind() const;
	void Unbind() const ;
};