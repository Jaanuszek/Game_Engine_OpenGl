#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "objects/Solid.h"
#include "Mesh.h"
#include <vector>

class MeshFactory {
public:
	static Mesh CreateMesh (Solid& solid, std::vector<Texture>& textures);
	static Mesh CreateMesh (Solid& solid, std::vector<TextureStruct>& textures);
};

#endif