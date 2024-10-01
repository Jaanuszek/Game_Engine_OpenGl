#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

#include <memory>
#include <vector>
#include "Mesh.h"
#include "VBO.h"
#include "objects/Solid.h"

class IObjectFactory {
public:
	virtual std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const = 0;
};

#endif