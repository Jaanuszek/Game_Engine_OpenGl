#ifndef SPHEREFACTORY_H
#define SPHEREFACTORY_H

#include "IObjectFactory.h"
#include "Sphere.h"

class SphereFactory : public IObjectFactory {
public:
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(Sphere(0.5f, 48, 48), vecSelectedTexture);
	}
};

#endif