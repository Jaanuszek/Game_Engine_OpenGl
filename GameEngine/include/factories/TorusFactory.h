#ifndef TORUSFACTORY_H
#define TORUSFACTORY_H

#include "IObjectFactory.h"
#include "Torus.h"

class TorusFactory : public IObjectFactory {
private:
	Torus& m_torus;
public:
	explicit TorusFactory(Torus& torus) : m_torus(torus) {}
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(m_torus, vecSelectedTexture);
	}
	Solid& GetSolidObject() override {
		return m_torus;
	}
};

#endif
