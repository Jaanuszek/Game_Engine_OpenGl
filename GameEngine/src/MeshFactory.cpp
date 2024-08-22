#include "MeshFactory.h"

Mesh MeshFactory::CreateMesh(Solid& solid, std::vector<Texture>& textures)
{
	//solid.Initalize();
	std::vector<Vertex> vertices = solid.GetVertices();
	std::vector<unsigned int> indices = solid.GetIndices();
	return Mesh(vertices,indices, textures);
}
