#ifndef PYRAMIDFACTORY_H
#define PYRAMIDFACTORY_H

#include "IObjectFactory.h"
#include "Pyramid.h"

class PyramidFactory : public IObjectFactory {
private:
	Pyramid& m_pyramid;
public:
	explicit PyramidFactory(Pyramid& pyramid) : m_pyramid(pyramid) {}
	std::shared_ptr<Mesh> CreateMesh(const std::vector<TextureStruct>& vecSelectedTexture) const override {
		return std::make_shared<Mesh>(m_pyramid, vecSelectedTexture);
	}
	Solid& GetSolidObject() override {
		return m_pyramid;
	}
};

#endif