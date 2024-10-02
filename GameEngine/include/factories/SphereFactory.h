#ifndef SPHEREFACTORY_H
#define SPHEREFACTORY_H

#include "IObjectFactory.h"
#include "Sphere.h"

class SphereFactory : public IObjectFactory {
private:
	Sphere& m_sphere;
public:
	explicit SphereFactory(Sphere& sphere) : m_sphere(sphere) {}
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(m_sphere, vecSelectedTexture);
	}
	Solid& GetSolidObject() override {
		return m_sphere;
	}
};

#endif