#ifndef MESH_UPDATER_H
#define MESH_UPDATER_H

#include "VBO.h"
#include "Mesh.h"
#include "factories/IObjectFactory.h"
#include "MeshRegistry.h"

class MeshUpdater {
public:
	static void UpdateObjectParams(const RenderObject& renderObject,
		MeshRegistry& meshRegistry, const std::vector<TextureStruct>& selectedTexture);
};

#endif