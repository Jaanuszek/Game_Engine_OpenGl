#ifndef CONEFACTORY_H
#define CONEFACTORY_H

#include "IObjectFactory.h"
#include "Cone.h"

class ConeFactory : public IObjectFactory {
private:
    Cone& m_cone;
public:
	explicit ConeFactory(Cone& cone) : m_cone(cone) {}
    std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
        return std::make_shared<Mesh>(m_cone,vecSelectedTexture);
    }
	Solid& GetSolidObject() override {
		return m_cone;
	}
};

#endif