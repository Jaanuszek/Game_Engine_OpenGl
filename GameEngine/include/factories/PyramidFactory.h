#ifndef PYRAMIDFACTORY_H
#define PYRAMIDFACTORY_H

#include "IObjectFactory.h"
#include "Pyramid.h"

class PyramidFactory : public IObjectFactory {
public:
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(Pyramid(), vecSelectedTexture);
	}
};

#endif