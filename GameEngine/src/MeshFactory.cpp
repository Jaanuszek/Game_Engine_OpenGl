#include "MeshFactory.h"

Mesh MeshFactory::CreateMesh(Solid& solid, std::vector<Texture>& textures)
{
	std::vector<Vertex> vertices = solid.GetVertices();
	std::vector<unsigned int> indices = solid.GetIndices();
	return Mesh(vertices,indices, textures);
}

Mesh MeshFactory::CreateMesh(Solid& solid, std::vector<TextureStruct>& textures)
{
	std::vector<Vertex> vertices = solid.GetVertices();
	std::vector<unsigned int> indices = solid.GetIndices();
	return Mesh(vertices, indices, textures);
}