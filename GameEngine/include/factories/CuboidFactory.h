#ifndef CUBOIDFACTORY_H
#define CUBOIDFACTORY_H

#include "IObjectFactory.h"
#include "Cuboid.h"

class CuboidFactory : public IObjectFactory {
private:
	Cuboid& m_cuboid;
public:
	explicit CuboidFactory(Cuboid& cuboid) : m_cuboid(cuboid) {}
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(m_cuboid, vecSelectedTexture);
	}
	Solid& GetSolidObject() override {
		return m_cuboid;
	}
};

#endif
