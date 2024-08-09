#ifndef VBO_H
#define VBO_H	

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>


struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Color;
	glm::vec3 Normal;
};

struct TextureStruct {
	unsigned int id;
	std::string type;
};

class VBO {
private:
	unsigned int m_ID;
public:
	VBO(const void* data, unsigned int size);
	VBO(std::vector<Vertex>& vertices);
	~VBO();

	void Bind() const;
	void Unbind() const;
	void Update(const void* data, unsigned int size) const;
};

#endif