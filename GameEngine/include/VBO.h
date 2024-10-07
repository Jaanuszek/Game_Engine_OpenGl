#ifndef VBO_H
#define VBO_H	

#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Camera.h"

// Consider moving these structs to a separate file
struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct TextureStruct {
	unsigned int id;
	std::string type;
	std::string path;
};

enum class RenderObject {
	Cube,
	Cuboid,
	Cylinder,
	Cone,
	Pyramid,
	Sphere,
	Torus,
	Assimp
};

enum class ShaderType {
	Basic = 0,
	CustomModel = 1,
	LightCube = 2,
	Lightning = 3,
	Sphere = 4
};

struct ShadersParams {
	ShaderType shaderType;
	glm::mat4 mvp;
	glm::mat4 model;
	glm::vec3 lightPos;
	Camera* camera;
};

class VBO {
private:
	unsigned int m_ID;
	unsigned int m_currentSizeOfBuffer;
public:
	VBO(const void* data, unsigned int size);
	VBO(std::vector<Vertex>& vertices);
	~VBO();

	void Bind() const;
	void Unbind() const;
	void Update(const std::vector<Vertex>& vertices);
};

#endif