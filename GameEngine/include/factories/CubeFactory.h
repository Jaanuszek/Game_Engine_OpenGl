#ifndef CUBEFACTORY_H
#define CUBEFACTORY_H

#include "IObjectFactory.h"
#include "Cube.h"

class CubeFactory : public IObjectFactory {
private:
	Cube& m_cube;
public:
	explicit CubeFactory(Cube& cube) : m_cube(cube) {}
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(m_cube, vecSelectedTexture);
	}
	Solid& GetSolidObject() override {
		return m_cube;
	}
};

#endif // !CUBEFACTORY_H
