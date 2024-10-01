#ifndef CYLINDERFACTORY_H
#define CYLINDERFACTORY_H

#include "IObjectFactory.h"
#include "Cylinder.h"

class CylinderFactory : public IObjectFactory {
public:
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(Cylinder(), vecSelectedTexture);
	}
};

#endif
