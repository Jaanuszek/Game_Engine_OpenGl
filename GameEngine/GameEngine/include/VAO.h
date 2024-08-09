#ifndef VAO_H
#define VAO_H

#include "VBO.h"
class VBL; //forward declaration informs compiler that VBL exusts abd will be defined later

class VAO {
private:
	unsigned int m_RendererID;
public:
	VAO();
	~VAO();

	void AddBuffer(const VBO& vbo, const VBL& layout);
	void Bind() const;
	void Unbind() const;
};

#endif