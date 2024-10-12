#include "MeshRegistry.h"

void MeshRegistry::CrateAndAddMeshToMap() {
	for (auto& object : m_vecObjects) {
		std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>> meshAndFactory = MeshFactory::CreateMeshFromFactory(object.first, object.second, m_vecSelectedTexture);
		// Emplace, because sunique_ptr is not copyable but movable, and Emplace creates the object in place 
		// std::move() is used to transfer ownership of the unique_ptr to the map
		m_meshMap.emplace(object.first, std::move(meshAndFactory));
	}
}

MeshRegistry::MeshRegistry(std::vector<std::pair<RenderObject, Solid&>>& vecObjects, std::vector<TextureStruct>& vecSelectedTexture)
	: m_vecObjects(vecObjects), m_vecSelectedTexture(vecSelectedTexture)
{
	CrateAndAddMeshToMap();
}

Mesh& MeshRegistry::GetMeshFromMap(RenderObject renderObject) {
	auto meshMapIterator = m_meshMap.find(renderObject);
	if (meshMapIterator == m_meshMap.end()) {
		throw std::runtime_error("RenderObject not found in meshMap");
	}
	return *meshMapIterator->second.first;
}

IObjectFactory* MeshRegistry::GetFactoryFromMap(RenderObject renderObject) {
	auto meshMapIterator = m_meshMap.find(renderObject);
	if (meshMapIterator == m_meshMap.end()) {
		throw std::runtime_error("RenderObject not found in meshMap");
	}
	// .get() returns the raw pointer (dereferenced)
	return meshMapIterator->second.second.get();
}
