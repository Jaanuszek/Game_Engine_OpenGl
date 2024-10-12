#include "factories/MeshFactory.h"

std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>> MeshFactory::CreateMeshFromFactory(RenderObject renderObject, Solid& solid, const std::vector<TextureStruct>& vecSelectedTexture) {
	std::unique_ptr<IObjectFactory> factory = ObjectFactory::GetFactory(renderObject, solid);
	std::shared_ptr<Mesh> mesh = factory->CreateMesh(vecSelectedTexture);
	return std::make_pair(mesh, std::move(factory));
}

//void MeshFactory::AddMeshToMap(RenderObject renderObject, Solid& solid,
//	std::map<RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>>& meshMap,
//	const std::vector<TextureStruct>& vecSelectedTexture) {
//	std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>> meshAndFactory = CreateMeshFromFactory(renderObject, solid, vecSelectedTexture);
//	// Emplace, because sunique_ptr is not copyable but movable, and Emplace creates the object in place 
//	// std::move() is used to transfer ownership of the unique_ptr to the map
//	meshMap.emplace(renderObject, std::move(meshAndFactory));
//}