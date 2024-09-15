#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

class EBO {
private:
	unsigned int m_ID;
	unsigned int m_Count;
	unsigned int m_currentSize;
public:
	EBO(const unsigned int* data, unsigned int count);
	EBO(std::vector<GLuint>& indices);
	~EBO();

	void Bind() const;
	void Unbind() const;
	void Update(const unsigned int* data, unsigned int count);
	void Update(std::vector<unsigned int>& indices);

	inline unsigned int GetCount() const { return m_Count; }
};

#endif