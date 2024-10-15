#ifndef MESH_REGISTRY_H
#define MESH_REGISTRY_H

#include <map>
#include "VBO.h"
#include "Mesh.h"
#include "Shader.h"
#include "factories/ObjectFactory.h"
#include "factories/MeshFactory.h"

class MeshRegistry {
private:
	std::vector<std::pair<RenderObject, Solid*>> m_vecObjects;
	std::map<RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>> m_meshMap;
	std::vector<TextureStruct>& m_vecSelectedTexture;
	void CrateAndAddMeshToMap();
public:
	MeshRegistry(std::vector<std::pair<RenderObject, Solid*>>& vecObjects, std::vector<TextureStruct>& vecSelectedTexture);
	MeshRegistry(const MeshRegistry& other);
	MeshRegistry& operator=(const MeshRegistry& other);
	MeshRegistry(MeshRegistry&& other) noexcept;
	MeshRegistry& operator=(MeshRegistry&& other) noexcept;
	std::map < RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>>& GetMeshMap() { return m_meshMap; }
	Mesh& GetMeshFromMap(RenderObject renderObject);
	IObjectFactory* GetFactoryFromMap(RenderObject renderObject);
	std::vector<TextureStruct>& GetVecSelectedTexture() { return m_vecSelectedTexture; }
	std::vector<std::pair<RenderObject, Solid*>>& GetVecObjects() { return m_vecObjects; }
};

#endif
