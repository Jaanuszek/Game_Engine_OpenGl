#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "VBO.h"
#include <memory>
#include "Mesh.h"
#include "factories/ObjectFactory.h"
#include "objects/Solid.h"
#include <map>

class MeshFactory
{
public:
	static std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>> CreateMeshFromFactory(RenderObject renderObject, Solid& solid, const std::vector<TextureStruct>& vecSelectedTexture);
	static void AddMeshToMap(RenderObject renderObject, Solid& solid,
		std::map<RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>>& meshMap,
		const std::vector<TextureStruct>& vecSelectedTexture);
};

#endif