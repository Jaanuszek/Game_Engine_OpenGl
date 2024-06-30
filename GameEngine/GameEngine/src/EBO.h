#pragma once

class EBO {
private:
	unsigned int m_ID;
	unsigned int m_Count;
public:
	EBO(const unsigned int* data, unsigned int count);
	~EBO();

	void Bind() const;
	void Unbind() const;
	void Update(const unsigned int* data, unsigned int count);

	inline unsigned int GetCount() const { return m_Count; }
};