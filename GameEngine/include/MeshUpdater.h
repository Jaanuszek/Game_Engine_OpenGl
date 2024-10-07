#ifndef MESH_UPDATER_H
#define MESH_UPDATER_H

#include "VBO.h"
#include "Mesh.h"

class MeshUpdater {
public:
	static void UpdateObjectParams(const RenderObject& renderObject,
		const std::map<RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>>& meshMap,
		const std::vector<TextureStruct>& selectedTexture) {
		auto meshMapIterator = meshMap.find(renderObject);
		if (meshMapIterator == meshMap.end()) {
			throw std::runtime_error("RenderObject not found in meshMap");
		}
		std::shared_ptr<Mesh> mesh = meshMap.find(renderObject)->second.first;
		IObjectFactory* factory = meshMap.find(renderObject)->second.second.get(); // .get() returns the raw pointer (dereferenced)
		Solid& solid = factory->GetSolidObject();
		solid.UpdateParams();
		mesh->updateMesh(solid.GetVertices(), solid.GetIndices(), selectedTexture);
	}
};

#endif