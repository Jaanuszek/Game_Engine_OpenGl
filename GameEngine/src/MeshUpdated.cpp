#include "MeshUpdater.h"

void MeshUpdater::UpdateObjectParams(const RenderObject& renderObject,
	MeshRegistry& meshRegistry, const std::vector<TextureStruct>& selectedTexture) {
	auto mesh = meshRegistry.GetMeshFromMap(renderObject);
	IObjectFactory* factory = meshRegistry.GetFactoryFromMap(renderObject);
	Solid& solid = factory->GetSolidObject();
	solid.UpdateParams();
	mesh.updateMeshParams(solid.GetVertices(), solid.GetIndices(), selectedTexture);
}