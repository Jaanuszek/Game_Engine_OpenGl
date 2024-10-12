#include "factories/MeshFactory.h"

std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>> MeshFactory::CreateMeshFromFactory(RenderObject renderObject, Solid& solid, const std::vector<TextureStruct>& vecSelectedTexture) {
	std::unique_ptr<IObjectFactory> factory = ObjectFactory::GetFactory(renderObject, solid);
	std::shared_ptr<Mesh> mesh = factory->CreateMesh(vecSelectedTexture);
	return std::make_pair(mesh, std::move(factory));
}