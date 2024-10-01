#ifndef CONEFACTORY_H
#define CONEFACTORY_H

#include "IObjectFactory.h"
#include "Cone.h"
#include "MeshFactory.h"

class ConeFactory : public IObjectFactory {
public:
    Cone& m_cone;
	ConeFactory(Cone& cone) :m_cone(cone)
    {
    }
    std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
        return std::make_shared<Mesh>(m_cone,vecSelectedTexture);
    }
};

#endif