#ifndef CYLINDERFACTORY_H
#define CYLINDERFACTORY_H

#include "IObjectFactory.h"
#include "Cylinder.h"

class CylinderFactory : public IObjectFactory {
private:
	Cylinder& m_cylinder;
public:
	explicit CylinderFactory(Cylinder& cylinder) : m_cylinder(cylinder) {}
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(m_cylinder, vecSelectedTexture);
	}
	Solid& GetSolidObject() override {
		return m_cylinder;
	}
};

#endif
