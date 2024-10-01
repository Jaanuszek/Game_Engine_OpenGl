#ifndef TORUSFACTORY_H
#define TORUSFACTORY_H

#include "IObjectFactory.h"
#include "Torus.h"

class TorusFactory : public IObjectFactory {
public:
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(Torus(0.2f, 0.5f, 48, 50), vecSelectedTexture);
	}
};

#endif
