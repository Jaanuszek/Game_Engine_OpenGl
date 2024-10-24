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
	try {
		switch (object) {
		case RenderObject::Cone:
			return std::make_unique<ConeFactory>(dynamic_cast<Cone&>(solid));
		case RenderObject::Cube:
			return std::make_unique<CubeFactory>(dynamic_cast<Cube&>(solid));
		case RenderObject::Cuboid:
			return std::make_unique<CuboidFactory>(dynamic_cast<Cuboid&>(solid));
		case RenderObject::Cylinder:
			return std::make_unique<CylinderFactory>(dynamic_cast<Cylinder&>(solid));
		case RenderObject::Pyramid:
			return std::make_unique<PyramidFactory>(dynamic_cast<Pyramid&>(solid));
		case RenderObject::Sphere:
			return std::make_unique<SphereFactory>(dynamic_cast<Sphere&>(solid));
		case RenderObject::Torus:
			return std::make_unique<TorusFactory>(dynamic_cast<Torus&>(solid));
		default:
			return nullptr;
		}
	}
	catch (const std::bad_cast& e) {
		std::cerr << "[ObjectFactory::GetFactory] Bad cast caught: " << e.what() << std::endl;
		throw;
	}
	catch (const std::exception& e) {
		std::cerr << "[ObjectFactory::GetFactory] Exception caught: " << e.what() << std::endl;
		throw;
	}
	catch (...) {
		std::cerr << "[ObjectFactory::GetFactory] Unknown exception caught" << std::endl;
		throw;
	}
}