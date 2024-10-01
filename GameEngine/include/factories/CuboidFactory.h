#ifndef CUBOIDFACTORY_H
#define CUBOIDFACTORY_H

#include "IObjectFactory.h"
#include "Cuboid.h"

class CuboidFactory : public IObjectFactory {
public:
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(Cuboid(0.75F,0.5F,0.5F), vecSelectedTexture);
	}
};

#endif
