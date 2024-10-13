#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>

class EBO {
private:
	unsigned int m_ID;
	unsigned int m_Count;
	unsigned int m_CurrentSize;
public:
	EBO(const std::vector<unsigned int>& indices);
	~EBO();

	void Bind() const;
	void Unbind() const;
	void Update(const std::vector<unsigned int>& indices);

	inline unsigned int GetCount() const { return m_Count; }
};

#endif