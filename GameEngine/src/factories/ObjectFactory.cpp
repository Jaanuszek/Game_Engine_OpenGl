#include "factories/ObjectFactory.h"
#include "factories/ConeFactory.h"
#include "factories/CubeFactory.h"
#include "factories/CuboidFactory.h"
#include "factories/CylinderFactory.h"
#include "factories/PyramidFactory.h"
#include "factories/SphereFactory.h"
#include "factories/TorusFactory.h"
#include <typeinfo>


std::unique_ptr<IObjectFactory> ObjectFactory::GetFactory(RenderObject object, Solid& solid) {
	switch (object) {
	case RenderObject::Cone:
		if (typeid(solid) == typeid(Cone))
		return std::make_unique<ConeFactory>(solid);
	case RenderObject::Cube:
		return std::make_unique<CubeFactory>();
	case RenderObject::Cuboid:
		return std::make_unique<CuboidFactory>();
	case RenderObject::Cylinder:
		return std::make_unique<CylinderFactory>();
	case RenderObject::Pyramid:
		return std::make_unique<PyramidFactory>();
	case RenderObject::Sphere:
		return std::make_unique<SphereFactory>();
	case RenderObject::Torus:
		return std::make_unique<TorusFactory>();
	default:
		return nullptr;
	}
}