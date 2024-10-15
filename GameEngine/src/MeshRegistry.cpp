#include "MeshRegistry.h"

void MeshRegistry::CrateAndAddMeshToMap() {
	for (auto& object : m_vecObjects) {
		std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>> meshAndFactory = MeshFactory::CreateMeshFromFactory(object.first, *object.second, m_vecSelectedTexture);
		// Emplace, because sunique_ptr is not copyable but movable, and Emplace creates the object in place 
		// std::move() is used to transfer ownership of the unique_ptr to the map
		m_meshMap.emplace(object.first, std::move(meshAndFactory));
	}
}

MeshRegistry::MeshRegistry(std::vector<std::pair<RenderObject, Solid*>>& vecObjects, std::vector<TextureStruct>& vecSelectedTexture)
	: m_vecObjects(vecObjects), m_vecSelectedTexture(vecSelectedTexture)
{
	CrateAndAddMeshToMap();
}

MeshRegistry::MeshRegistry(const MeshRegistry& other): m_vecObjects(other.m_vecObjects), m_vecSelectedTexture(other.m_vecSelectedTexture)  {
	CrateAndAddMeshToMap();
}
MeshRegistry& MeshRegistry::operator=(const MeshRegistry& other) {
	if (this == &other) {
		return *this;
	}
	//google test helped me fixing the bug
	//You can't copy reference, so i changed type of m_vecObjects vector to pinter to SOlid object
	//I can also do this using smart pointers
	m_vecObjects.clear();
	for (const auto& object : other.m_vecObjects) {
		m_vecObjects.emplace_back(object);
	}
	m_vecSelectedTexture = other.m_vecSelectedTexture;
	m_meshMap.clear();
	CrateAndAddMeshToMap();
	return *this;
}
MeshRegistry::MeshRegistry(MeshRegistry&& other) noexcept : m_vecObjects(std::move(other.m_vecObjects)), m_vecSelectedTexture(std::move(other.m_vecSelectedTexture)) {
	CrateAndAddMeshToMap();
}
MeshRegistry& MeshRegistry::operator=(MeshRegistry&& other) noexcept {
	if (this != &other) {
		m_vecObjects = std::move(other.m_vecObjects);
		m_vecSelectedTexture = std::move(other.m_vecSelectedTexture);
		m_meshMap = std::move(other.m_meshMap);
	}
	return *this;
}
Mesh& MeshRegistry::GetMeshFromMap(RenderObject renderObject) {
	auto meshMapIterator = m_meshMap.find(renderObject);
	if (meshMapIterator == m_meshMap.end()) {
		throw std::runtime_error("[MeshRegistry::GetMeshFromMap] RenderObject not found in meshMap");
	}
	return *meshMapIterator->second.first;
}

IObjectFactory* MeshRegistry::GetFactoryFromMap(RenderObject renderObject) {
	auto meshMapIterator = m_meshMap.find(renderObject);
	if (meshMapIterator == m_meshMap.end()) {
		throw std::runtime_error("[MeshRegistry::GetFactoryFromMap] RenderObject not found in meshMap");
	}
	// .get() returns the raw pointer (dereferenced)
	return meshMapIterator->second.second.get();
}
