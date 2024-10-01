#ifndef CUBEFACTORY_H
#define CUBEFACTORY_H

#include "IObjectFactory.h"
#include "Cube.h"

class CubeFactory : public IObjectFactory {
public:
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(Cube(), vecSelectedTexture);
	}
};

#endif // !CUBEFACTORY_H
